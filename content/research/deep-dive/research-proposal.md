+++
title = "Master's Research: Efficient Inference for LLMs"
date = 2025-01-05
draft = false
tags = ["research", "llm", "systems", "inference"]
description = "Overview of my master's research direction — reducing inference latency for large language models."
+++

## Motivation

Large language models have become indispensable, but their inference costs remain prohibitive. A single forward pass of a 70B parameter model requires ~140 GB of memory just to store weights (in FP16), making real-time serving expensive.

The core tension is:

- **Model quality** improves with scale
- **Inference cost** grows with scale (both memory and compute)
- **Latency requirements** are often strict (< 200ms for interactive use)

## Research Direction

My research focuses on **structured sparsity** during inference — specifically on exploiting activation patterns in transformer attention to skip unnecessary computation *without* accuracy loss.

The key observation is that attention matrices are naturally sparse: for most tokens, only a small fraction of other tokens receive significant attention weight. If we can *predict* which tokens matter before computing full attention, we can skip the rest.

## Preliminary Work

Initial experiments on LLaMA-2-7B show that:

- Top-1% of attention weights account for ~60% of attention output norm
- The sparsity pattern is somewhat predictable from the query/key norms

I'm currently implementing a speculative attention mechanism where:

1. A lightweight predictor (tiny MLP or locality-sensitive hashing) identifies the top-$k$ candidates
2. Full attention is computed only over those candidates
3. A correction pass handles the residual if necessary

## Next Steps

- Benchmark against FlashAttention-2 baseline on A100
- Evaluate on MMLU, HellaSwag, and ARC to check for accuracy regression
- Profile memory bandwidth vs compute trade-off at different sparsity levels
