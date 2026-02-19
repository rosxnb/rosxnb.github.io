+++
title = "Probability Fundamentals"
date = 2025-01-10
draft = false
series = ["Statistics for ML"]
tags = ["statistics", "probability", "math"]
math = true
description = "Core probability axioms, conditional probability, and Bayes' theorem."
+++

## Sample Space and Events

A **probability space** is a triple $(\Omega, \mathcal{F}, P)$ where:

- $\Omega$ is the sample space (set of all outcomes)
- $\mathcal{F}$ is a $\sigma$-algebra of events
- $P: \mathcal{F} \to [0,1]$ is a probability measure

The **Kolmogorov axioms** define $P$:

1. $P(A) \geq 0$ for all $A \in \mathcal{F}$
2. $P(\Omega) = 1$
3. For disjoint $A_1, A_2, \ldots$: $P\left(\bigcup_{i=1}^{\infty} A_i\right) = \sum_{i=1}^{\infty} P(A_i)$

## Conditional Probability

The conditional probability of $A$ given $B$ is:

$$P(A \mid B) = \frac{P(A \cap B)}{P(B)}, \quad P(B) > 0$$

{{< callout type="note" title="Intuition" >}}
Conditioning on $B$ means we restrict our universe to outcomes where $B$ occurred. Within that restricted universe, we ask how likely $A$ is.
{{< /callout >}}

## Bayes' Theorem

Bayes' theorem flips the conditioning:

$$P(A \mid B) = \frac{P(B \mid A) \cdot P(A)}{P(B)}$$

In the ML context, with hypothesis $H$ and data $D$:

$$\underbrace{P(H \mid D)}_{\text{posterior}} = \frac{\underbrace{P(D \mid H)}_{\text{likelihood}} \cdot \underbrace{P(H)}_{\text{prior}}}{\underbrace{P(D)}_{\text{evidence}}}$$

## Independence

Events $A$ and $B$ are **independent** if:

$$P(A \cap B) = P(A) \cdot P(B)$$

This is equivalent to $P(A \mid B) = P(A)$ — knowing $B$ gives no information about $A$.

{{< callout type="warning" title="Independence ≠ Mutually Exclusive" >}}
Two events can be mutually exclusive (disjoint) without being independent, and vice versa. In fact, for non-trivial events, mutual exclusivity and independence cannot both hold.
{{< /callout >}}

## Random Variables

A random variable $X: \Omega \to \mathbb{R}$ is a measurable function from the sample space to the reals.

For a discrete RV, the **PMF** is $p(x) = P(X = x)$.

For a continuous RV, the **PDF** $f(x)$ satisfies $P(a \leq X \leq b) = \int_a^b f(x)\,dx$.

The **CDF** is $F(x) = P(X \leq x)$, and for continuous RVs: $f(x) = F'(x)$.
