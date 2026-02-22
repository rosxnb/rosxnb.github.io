+++
title = "Unfiltered Thoughts"
date = 2026-02-01T00:43:39+05:45
tags = []
description = "List of raw ideas"
+++


## Digital Stamp

As AI-generated content (images, videos, music, code, etc.) proliferates, can we program a system that stamps any digital
stream (PDF, PNG, MP3, MP4, text, ...) with these properties:

- **Harmless integration**: Stamp addition leaves the digital stream uncorrupted—host applications can still
open, execute, or parse it successfully.

- **Harmful removal**: Forcibly removing the stamp corrupts the stream, rendering the content unusable/garbage.

---

## Optimize Model for repeated questions

Just as humans leverage subconscious mind or muscle memory to perform repeated tasks with ease, AI models should
be able to execute repeated actions cheaply.

- **Are current models optimized for this?** No—each query, even identical ones, is processed from scratch with similar
computational cost

- **How to test optimality?** Measure inference time/compute across multiple identical queries—an optimized model should
show progressively lower latency/resource usage
