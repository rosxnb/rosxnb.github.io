+++
title = "Unfiltered Thoughts"
date = 2026-02-22T00:43:39+05:45
tags = ["raw", "research"]
description = "Collection of random ideas that might be research worthy"
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

---

## Efficient Inference for LLMs

Large language models have become indispensable, but their inference costs remain prohibitive. A single forward pass of a 70B parameter model requires ~140 GB of memory just to store weights (in FP16), making real-time serving expensive.

The core tension is:

- **Model quality** improves with scale
- **Inference cost** grows with scale (both memory and compute)
- **Latency requirements** are often strict (< 200ms for interactive use)

My research focuses on **structured sparsity** during inference — specifically on exploiting activation patterns in transformer attention to skip unnecessary computation *without* accuracy loss.

The key observation is that attention matrices are naturally sparse: for most tokens, only a small fraction of other tokens receive significant attention weight. If we can *predict* which tokens matter before computing full attention, we can skip the rest.

Initial experiments on LLaMA-2-7B show that:

- Top-1% of attention weights account for ~60% of attention output norm
- The sparsity pattern is somewhat predictable from the query/key norms

I'm currently implementing a speculative attention mechanism where:

1. A lightweight predictor (tiny MLP or locality-sensitive hashing) identifies the top-$k$ candidates
2. Full attention is computed only over those candidates
3. A correction pass handles the residual if necessary

**Next steps**:

- Benchmark against FlashAttention-2 baseline on A100
- Evaluate on MMLU, HellaSwag, and ARC to check for accuracy regression
- Profile memory bandwidth vs compute trade-off at different sparsity levels
