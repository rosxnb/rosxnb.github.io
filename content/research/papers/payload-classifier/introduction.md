+++
title = "Introduction"
date = 2026-03-13T10:57:12+05:45
tags = []
description = "Extracting What Matters: A Domain-Agnostic Approach to User Payload Extraction from Network Traffic"
+++


Every time you type a message into Gmail, upload a file to Slack, or prompt ChatGPT, your words travel across the
network as raw bytes — wrapped in TLS, encoded in JSON or Protobuf, compressed, chunked, and multiplexed through
HTTP/2 streams. A MITM proxy can intercept all of this. The question I keep coming back to is deceptively simple:

> **Given the raw intercepted traffic, can we automatically extract just what the user gave to the application
> — without writing app-specific code for every service?**

This post is the beginning of an answer.

---

## The Problem, Precisely

When a MITM proxy terminates a TLS connection, you have plaintext. That part is solved. What isn't solved is the
semantic layer — distinguishing between:

- The **user payload**: the message text, the uploaded file, the email draft, the search query — content that
  originated from a human action.
- The **application payload**: session tokens, CSRF nonces, API version strings, pagination cursors, telemetry
  pings, client fingerprints — content that the application generates autonomously.

These two categories are deeply interleaved at the byte level. A single HTTP/2 POST to `mail.google.com` might carry
your email body nested three levels deep inside a serialized Protobuf message, alongside dozens of fields that are
entirely opaque infrastructure. A WebSocket frame to `chat.openai.com` carries your prompt somewhere inside a JSON
envelope alongside model parameters, conversation IDs, and streaming control signals.

The state of the art is: write a per-app decoder. Know the schema for Gmail, write a Gmail extractor. Know the schema
for ChatGPT, write a ChatGPT extractor. Repeat for every application, and repeat again every time an application changes
its wire format. This is exactly how commercial DLP (Data Loss Prevention) products like Zscaler and Netskope operate —
they maintain libraries of hundreds of application signatures, with dedicated teams keeping them current.

It works. It also doesn't scale, and it completely fails on any application not in the library.

---

## Why This Is Hard

Three sub-problems make this genuinely difficult, each harder than the last.

### 1. Protocol Heterogeneity

The modern web doesn't speak one protocol. REST over HTTP/1.1 is the easy case. But production traffic is increasingly
HTTP/2 with HPACK-compressed headers and multiplexed DATA frames, WebSocket with text and binary opcodes,
gRPC (which is HTTP/2 + length-prefixed Protobuf), and occasionally raw SSE (Server-Sent Events) streams. A general
extractor has to handle all of these correctly before it can even look at a payload.

### 2. Semantic Field Classification

Once you've decoded a JSON object or a multipart body, you're looking at a tree of fields. Some of them are user
content. Most of them aren't. A naive heuristic — "long strings are user content" — fails immediately on base64-encoded
file uploads (which look like tokens), short messages ("ok", "yes", "lol"), and deeply nested structures where the user
content is at an unpredictable path.

This is where classical methods begin to struggle. There is no universal rule that cleanly separates
"the thing the user typed" from "the thing the application generated" across all schemas, all services, and all content
types.

### 3. Schema-less Binary Serialization

The hardest sub-problem. Services like Google, Meta, and Instagram serialize their payloads as Protobuf without
publishing their `.proto` schema files. The wire format tells you a field number and a wire type (varint,
length-delimited, etc.) — but not what the field *means*. Field 7 in message type 42 could be a user's message body,
or it could be a server-assigned conversation ID. Without the schema, you cannot tell from structure alone.

This is the point where purely classical methods require either a known schema or per-domain reverse engineering.
Neither generalizes.

---

## What I Think Is Possible

The architecture I want to build is a five-stage pipeline:

```
Raw bytes → Protocol Decoder → Body Deserializer → Field Extractor → ML Classifier → Enriched Output
```

The first three stages are classical and largely solved — protocol parsers for HTTP/1.1, HTTP/2, WebSocket, and gRPC;
body deserializers for JSON, multipart, URL-encoded, and raw Protobuf wire format; a tree-walker that emits
`(path, value, metadata)` candidate tuples.

The fourth stage is the research contribution: a fine-tuned transformer-based classifier that scores each candidate
field on the probability that it is user-generated content. The key insight is that this classification does not
require knowing the application schema — it operates on the *content* of the field and its structural context. A
user-typed sentence has statistical properties (entropy, perplexity under a language model, character n-gram
distribution) that differ meaningfully from a UUID, a JWT, or a base64-encoded binary blob — regardless of which
application produced the surrounding structure.

For the Protobuf problem specifically, I am exploring two complementary approaches:

- **Statistical field profiling**: with enough traffic samples from a given service, cluster field values by type.
  A field that always contains valid UTF-8 with high lexical diversity is almost certainly a text field. A field with
  fixed-length, high-entropy byte sequences is almost certainly an ID or token.
- **Cross-request correlation**: if you intercept both a "send" request and a "fetch" response for the same service,
  the value that appears in the POST body and reappears in the GET response is causally user-generated. This correlation
  signal can label Protobuf fields without any schema knowledge.

---

## Why ML, and Why Not ML Alone

The temptation is to throw a large model at the raw bytes and call it done. The problem is that the signal you want is
deeply buried in noise, and inference over raw bytes is expensive. A more principled approach is to use classical
methods as a fast pre-filter — eliminate obvious non-candidates (short fixed-length fields, known token patterns,
numeric-only values) before running any model — and reserve the classifier for the ambiguous cases.

The ML component also needs to generalize in a specific way: not across arbitrary NLP tasks, but across the specific
distribution of "user content vs. application metadata" as it appears in real web traffic. That calls for a fine-tuned
model with a purpose-built training corpus, not a general-purpose LLM.

The industry data point here is instructive: commercial DLP systems that have incorporated ML report roughly 85–95%
recall on payload extraction across their covered application libraries. The schema-less binary case remains the open
problem — that is where the research gap lives.

---

## What This Project Is Not

To be clear about scope: this is not a surveillance tool, and the design does not assume an adversarial relationship
between the proxy operator and the user. The intended contexts are enterprise DLP (where employees consent to
monitoring), digital forensics (under legal authority), AI safety auditing (inspecting what leaves a device toward
LLM APIs), and privacy research (auditing what applications actually transmit). The payload extractor is a
component — the ethical framing of any system that uses it is a separate and important question.

---

## What Comes Next

This is the first post in what I expect to be a longer series. The immediate next steps are:

1. **Build the protocol decoder layer** — handling HTTP/1.1, HTTP/2, and WebSocket correctly, with a clean intermediate
   representation that subsequent stages can consume uniformly.
2. **Assemble a labeled dataset** — intercepted traffic across a range of applications (Gmail, Outlook, WhatsApp Web,
   ChatGPT, Claude, Slack) with ground-truth user payload labels. This is the hardest practical step.
3. **Baseline heuristics** — before training anything, establish how well entropy thresholds, length filters, and
   UTF-8 validity checks perform as a zero-ML baseline.
4. **Fine-tune the classifier** — starting with DistilBERT as the backbone; evaluating on held-out applications not seen
   during training to test generalization.

The Protobuf sub-problem will get its own post. It deserves the space.

If you are working on something adjacent — network traffic analysis, DLP systems, protocol reverse engineering, or
privacy auditing — I would genuinely like to hear from you. The dataset labeling problem in particular is one I have
not fully solved, and collaboration would help.

---

*This post is part research work. Ideas here are exploratory and evolving — I will update this
post and link to follow-up work as the project develops.*
