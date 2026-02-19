+++
title = "Expectation and Variance"
date = 2025-01-17
draft = false
series = ["Statistics for ML"]
tags = ["statistics", "probability", "math"]
math = true
description = "Expected value, variance, covariance, and moment generating functions."
+++

## Expected Value

The expectation (mean) of a random variable $X$:

$$\mathbb{E}[X] = \begin{cases} \sum_x x \cdot p(x) & \text{discrete} \\ \int_{-\infty}^{\infty} x \cdot f(x)\,dx & \text{continuous} \end{cases}$$

**Key properties** (by linearity):
- $\mathbb{E}[aX + b] = a\mathbb{E}[X] + b$
- $\mathbb{E}[X + Y] = \mathbb{E}[X] + \mathbb{E}[Y]$ (always, no independence needed)
- $\mathbb{E}[XY] = \mathbb{E}[X]\mathbb{E}[Y]$ *only if* $X \perp Y$

## Variance

$$\text{Var}(X) = \mathbb{E}[(X - \mu)^2] = \mathbb{E}[X^2] - (\mathbb{E}[X])^2$$

where $\mu = \mathbb{E}[X]$. The **standard deviation** is $\sigma = \sqrt{\text{Var}(X)}$.

Properties:
- $\text{Var}(aX + b) = a^2 \text{Var}(X)$
- $\text{Var}(X + Y) = \text{Var}(X) + \text{Var}(Y) + 2\,\text{Cov}(X, Y)$

## Covariance and Correlation

$$\text{Cov}(X, Y) = \mathbb{E}[(X - \mu_X)(Y - \mu_Y)] = \mathbb{E}[XY] - \mu_X \mu_Y$$

The **Pearson correlation coefficient** normalises this to $[-1, 1]$:

$$\rho_{XY} = \frac{\text{Cov}(X, Y)}{\sigma_X \sigma_Y}$$

{{< callout type="tip" title="Correlation ≠ Causation" >}}
$\rho \approx 0$ means no *linear* relationship, but there could be a strong nonlinear one. And even high $|\rho|$ says nothing about causation.
{{< /callout >}}

## Moment Generating Functions

The MGF of $X$ is $M_X(t) = \mathbb{E}[e^{tX}]$, when it exists in a neighbourhood of $t = 0$.

The $n$-th moment satisfies:

$$\mathbb{E}[X^n] = M_X^{(n)}(0)$$

MGFs uniquely determine distributions (when they exist), which makes them powerful for proving convergence theorems.
