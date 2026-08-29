+++
title = "Backpropagation from Scratch"
date = 2025-02-01
draft = false
series = ["Deep Learning Fundamentals"]
tags = ["deep-learning", "neural-networks", "math"]
math = true
description = "Deriving backpropagation using the chain rule. With a working Python implementation."
+++

## The Setup

A neural network is a composition of functions. For a two-layer net:

$$\hat{y} = f(W_2 \cdot \sigma(W_1 x + b_1) + b_2)$$

We want to minimise a loss $\mathcal{L}(\hat{y}, y)$ with respect to all parameters $\{W_1, b_1, W_2, b_2\}$.

Backpropagation is just the **chain rule**, applied systematically from the output layer backwards.

## The Chain Rule

For a scalar loss and composed functions $z = g(f(x))$:

$$\frac{dz}{dx} = \frac{dz}{dg} \cdot \frac{dg}{dx}$$

For vectors and matrices, this generalises to Jacobians.

## Forward and Backward Pass

For layer $l$ with pre-activation $z^{(l)} = W^{(l)} a^{(l-1)} + b^{(l)}$ and activation $a^{(l)} = \sigma(z^{(l)})$:

**Forward pass** — compute and cache:
$$z^{(l)},\quad a^{(l)} \text{ for all } l$$

**Backward pass** — compute deltas:
$$\delta^{(L)} = \nabla_{a^{(L)}} \mathcal{L} \odot \sigma'(z^{(L)})$$

$$\delta^{(l)} = \left((W^{(l+1)})^\top \delta^{(l+1)}\right) \odot \sigma'(z^{(l)})$$

**Gradients:**
$$\frac{\partial \mathcal{L}}{\partial W^{(l)}} = \delta^{(l)} (a^{(l-1)})^\top, \qquad \frac{\partial \mathcal{L}}{\partial b^{(l)}} = \delta^{(l)}$$

## Python Implementation

```python
import numpy as np

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def sigmoid_prime(z):
    s = sigmoid(z)
    return s * (1 - s)

def mse_loss(y_hat, y):
    return 0.5 * np.mean((y_hat - y) ** 2)

def forward(X, W1, b1, W2, b2):
    """Returns activations and pre-activations (cache for backprop)."""
    z1 = W1 @ X + b1
    a1 = sigmoid(z1)
    z2 = W2 @ a1 + b2
    a2 = sigmoid(z2)   # output (for binary classification)
    return a2, (z1, a1, z2, a2)

def backward(X, y, cache, W2):
    z1, a1, z2, a2 = cache
    m = X.shape[1]

    # Output layer delta
    dL_da2 = (a2 - y)          # dL/d(a2) for MSE
    delta2 = dL_da2 * sigmoid_prime(z2)

    # Hidden layer delta
    delta1 = (W2.T @ delta2) * sigmoid_prime(z1)

    # Gradients
    dW2 = (delta2 @ a1.T) / m
    db2 = delta2.mean(axis=1, keepdims=True)
    dW1 = (delta1 @ X.T) / m
    db1 = delta1.mean(axis=1, keepdims=True)

    return dW1, db1, dW2, db2
```

{{< callout type="tip" title="Numerical gradient check" >}}
Always verify your backprop with finite differences during development:
$\frac{\partial \mathcal{L}}{\partial \theta} \approx \frac{\mathcal{L}(\theta + \epsilon) - \mathcal{L}(\theta - \epsilon)}{2\epsilon}$
for small $\epsilon \approx 10^{-5}$.
{{< /callout >}}

## Why Caching Matters

Notice that the forward pass caches $z^{(l)}$ and $a^{(l)}$. During backprop, we reuse these instead of recomputing — which is the key efficiency gain. Without caching, backprop would be as expensive as naively computing all gradients separately.
