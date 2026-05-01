+++
title = "Modern Perceptron and Activations"
date = 2026-05-01T15:03:26+05:45
tags = ["perceptron", "threshold-method", "activation-functions"]
math = true
description = "A better way to visualize perceptron and activation units"
+++

## A Better Model: The Modern Perceptron

By slightly shifting our notation, we can represent the perceptron in a much more flexible way. Instead of treating the threshold $T$ as a separate logical condition,
we can incorporate it directly into the input summation as a bias term, where the bias is simply the negative threshold ($b = -T$). 

This allows us to describe the perceptron as a clean, two-step structural pipeline:
1. **An Affine Combination**: The structure first computes an affine combination of the inputs and weights to produce an intermediate value $z$.
$$z = \sum_{i} w_i x_i + b$$
2. **An Activation Function ($\theta$)**: This intermediate value $z$ is then passed through an activation function to determine the final output $y$.

In a basic, classic perceptron, this activation function is a very simple step-wise function: the output is 1 if the input is non-negative, and 0 otherwise.

$$
y = \begin{cases} 
1 & \text{if } z \ge 0 \\\\ 
0 & \text{otherwise} 
\end{cases}
$$

However, by separating the affine input from the decision method, we are no longer limited to rigid boolean threshold outputs. Once we have the $\theta$ notation, we can substitute the step
function with other continuous or differentiable activation functions, such as Sigmoid, Tanh, and ReLU.

{{< callout type="note" title="Linear vs. Affine Combination" >}}
While often used interchangeably in casual discussion, there is a strict mathematical distinction between a *linear* combination and an *affine* combination. 

- **Linear Combination**: A sum of scaled inputs ($w_1 x_1 + w_2 x_2$). Geometrically, this restricts the resulting boundary line or hyperplane to always pass exactly through the origin (0,0).
- **Affine Combination**: A linear combination plus an offset or translation ($w_1 x_1 + w_2 x_2 + b$). The addition of the bias term ($b$) allows the boundary to shift away from the origin,
  giving the model the freedom to fit patterns anywhere in the mathematical space.

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 700 350" style="width: 100%; height: auto; max-width: 700px; display: block; margin: 1.5rem auto; background-color: #f8fafc; border-radius: 8px; border: 1px solid #e2e8f0;">
  <defs>
    <marker id="arrow" markerWidth="10" markerHeight="10" refX="9" refY="3" orient="auto">
      <path d="M0,0 L0,6 L9,3 z" fill="#64748b" />
    </marker>
  </defs>
  <g stroke="#e2e8f0" stroke-width="1">
    <line x1="50" y1="50" x2="650" y2="50" />
    <line x1="50" y1="100" x2="650" y2="100" />
    <line x1="50" y1="150" x2="650" y2="150" />
    <line x1="50" y1="200" x2="650" y2="200" />
    <line x1="50" y1="250" x2="650" y2="250" />
    <line x1="50" y1="300" x2="650" y2="300" />
    <line x1="150" y1="30" x2="150" y2="320" />
    <line x1="250" y1="30" x2="250" y2="320" />
    <line x1="350" y1="30" x2="350" y2="320" />
    <line x1="450" y1="30" x2="450" y2="320" />
    <line x1="550" y1="30" x2="550" y2="320" />
  </g>
  <line x1="50" y1="200" x2="650" y2="200" stroke="#64748b" stroke-width="2" marker-end="url(#arrow)" />
  <line x1="350" y1="320" x2="350" y2="30" stroke="#64748b" stroke-width="2" marker-end="url(#arrow)" />
  <text x="635" y="190" font-family="sans-serif" font-size="14" fill="#64748b">X</text>
  <text x="360" y="45" font-family="sans-serif" font-size="14" fill="#64748b">Y</text>
  <text x="330" y="215" font-family="sans-serif" font-size="14" fill="#64748b">0</text>
  <line x1="100" y1="300" x2="600" y2="100" stroke="#3b82f6" stroke-width="3" />
  <text x="490" y="160" font-family="sans-serif" font-size="16" fill="#3b82f6" font-weight="bold">Linear: y = wx</text>
  <line x1="100" y1="230" x2="600" y2="30" stroke="#ef4444" stroke-width="3" />
  <text x="140" y="115" font-family="sans-serif" font-size="16" fill="#ef4444" font-weight="bold">Affine: y = wx + b</text>
  <line x1="350" y1="200" x2="350" y2="130" stroke="#10b981" stroke-width="3" stroke-dasharray="4" />
  <circle cx="350" cy="130" r="5" fill="#ef4444" />
  <text x="360" y="170" font-family="sans-serif" font-size="16" fill="#10b981" font-weight="bold">Bias (b)</text>
</svg>
{{< /callout >}}

## Common Activation Functions

The separation of the affine transformation from the activation step unlocked the true potential of neural networks. By replacing the non-differentiable step function with continuous curves, researchers
could use calculus (specifically, the chain rule) to update weights. This led to the widespread adoption of backpropagation.

---

### Sigmoid (Logistic) Function

**Paper**: *Learning representations by back-propagating errors* by David Rumelhart, Geoffrey Hinton, and Ronald Williams, 1986.

The sigmoid function was critical to the first wave of deep learning. It was heavily utilized and popularized in the 1986 seminal paper by David Rumelhart et al. Because the step function has a derivative of zero almost
everywhere (making gradient descent impossible), the sigmoid provided a smooth, differentiable alternative that "squashed" outputs into a valid probability range between 0 and 1.

**Mathematical Definition:**
$$\sigma(z) = \frac{1}{1 + e^{-z}}$$

**Derivative and Derivation:**
A beautiful property of the sigmoid function is that its derivative can be expressed entirely in terms of its own output, which makes computing gradients extremely fast.
$$
\begin{aligned}
\sigma'(z) &= \frac{d}{dz} (1 + e^{-z})^{-1} \\\\
&= -(1 + e^{-z})^{-2} (-e^{-z}) \\\\
&= \frac{e^{-z}}{(1 + e^{-z})^2} \\\\
&= \left( \frac{1}{1 + e^{-z}} \right) \left( \frac{e^{-z}}{1 + e^{-z}} \right) \\\\
&= \sigma(z) \left( \frac{(1 + e^{-z}) - 1}{1 + e^{-z}} \right) \\\\
&= \sigma(z) (1 - \sigma(z))
\end{aligned}
$$

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 500 300" style="width: 100%; height: auto; max-width: 500px; display: block; margin: 1.5rem auto; background-color: #ffffff; border-radius: 8px; border: 1px solid #e2e8f0;">
  <defs>
    <marker id="arrow-sig" markerWidth="10" markerHeight="10" refX="9" refY="3" orient="auto">
      <path d="M0,0 L0,6 L9,3 z" fill="#64748b" />
    </marker>
  </defs>
  <g stroke="#e2e8f0" stroke-width="1">
    <line x1="50" y1="50" x2="450" y2="50" />
    <line x1="50" y1="150" x2="450" y2="150" />
    <line x1="116.6" y1="50" x2="116.6" y2="250" />
    <line x1="183.3" y1="50" x2="183.3" y2="250" />
    <line x1="316.6" y1="50" x2="316.6" y2="250" />
    <line x1="383.3" y1="50" x2="383.3" y2="250" />
    <line x1="450" y1="50" x2="450" y2="250" />
  </g>
  <line x1="50" y1="250" x2="470" y2="250" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-sig)" />
  <line x1="250" y1="250" x2="250" y2="30" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-sig)" />
  <polyline points="50,249.6 66.6,249.2 83.3,248.8 100,247.8 116.6,246.4 133.3,244 150,240.6 166.6,234.8 183.3,226.2 200,213.6 216.6,196.2 233.3,174.6 250,150 266.6,125.6 283.3,103.8 300,86.6 316.6,73.8 333.3,65.2 350,59.4 366.6,56 383.3,53.6 400,52.2 416.6,51.4 433.3,50.8 450,50.4" fill="none" stroke="#3b82f6" stroke-width="3" stroke-linejoin="round" />
  <text x="50" y="270" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">-6</text>
  <text x="116.6" y="270" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">-4</text>
  <text x="183.3" y="270" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">-2</text>
  <text x="250" y="270" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">0</text>
  <text x="316.6" y="270" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">2</text>
  <text x="383.3" y="270" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">4</text>
  <text x="450" y="270" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">6</text>
  <text x="240" y="154" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="end">0.5</text>
  <text x="240" y="54" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="end">1.0</text>
</svg>

---

### Tanh (Hyperbolic Tangent)

**Paper**: *Efficient BackProp* by Yann LeCun, 1998.

As neural networks grew slightly larger in the 1990s, researchers noticed that the sigmoid function often slowed down learning because its outputs were strictly positive (not zero-centered).
Yann LeCun's 1998 paper strongly advocated for the Tanh function. By shifting the curve to range between -1 and 1, the data remains zero-centered, which helps the gradients point closer to the
true optimal direction during optimization, leading to faster convergence.

**Mathematical Definition:**
$$\tanh(z) = \frac{e^z - e^{-z}}{e^z + e^{-z}}$$

**Derivative and Derivation:**
Like the sigmoid, the derivative of the Tanh function cleanly reduces to a formula based on its own output. Using the quotient rule:
$$
\begin{aligned}
\frac{d}{dz} \tanh(z) &= \frac{d}{dz} \left( \frac{e^z - e^{-z}}{e^z + e^{-z}} \right) \\\\
&= \frac{(e^z + e^{-z})(e^z + e^{-z}) - (e^z - e^{-z})(e^z - e^{-z})}{(e^z + e^{-z})^2} \\\\
&= \frac{(e^z + e^{-z})^2}{(e^z + e^{-z})^2} - \frac{(e^z - e^{-z})^2}{(e^z + e^{-z})^2} \\\\
&= 1 - \tanh^2(z)
\end{aligned}
$$

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 500 300" style="width: 100%; height: auto; max-width: 500px; display: block; margin: 1.5rem auto; background-color: #ffffff; border-radius: 8px; border: 1px solid #e2e8f0;">
  <defs>
    <marker id="arrow-tanh" markerWidth="10" markerHeight="10" refX="9" refY="3" orient="auto">
      <path d="M0,0 L0,6 L9,3 z" fill="#64748b" />
    </marker>
  </defs>
  <g stroke="#e2e8f0" stroke-width="1" stroke-dasharray="4">
    <line x1="50" y1="50" x2="450" y2="50" />
    <line x1="50" y1="100" x2="450" y2="100" />
    <line x1="50" y1="200" x2="450" y2="200" />
    <line x1="50" y1="250" x2="450" y2="250" />
    <line x1="116.6" y1="50" x2="116.6" y2="250" />
    <line x1="183.3" y1="50" x2="183.3" y2="250" />
    <line x1="316.6" y1="50" x2="316.6" y2="250" />
    <line x1="383.3" y1="50" x2="383.3" y2="250" />
    <line x1="450" y1="50" x2="450" y2="250" />
  </g>
  <line x1="50" y1="150" x2="470" y2="150" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-tanh)" />
  <line x1="250" y1="270" x2="250" y2="30" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-tanh)" />
  <polyline points="50,249.6 66.6,249.2 83.3,248.8 100,247.8 116.6,246.4 133.3,244 150,240.6 166.6,234.8 183.3,226.2 200,213.6 216.6,196.2 233.3,174.6 250,150 266.6,125.6 283.3,103.8 300,86.6 316.6,73.8 333.3,65.2 350,59.4 366.6,56 383.3,53.6 400,52.2 416.6,51.4 433.3,50.8 450,50.4" fill="none" stroke="#8b5cf6" stroke-width="3" stroke-linejoin="round" />
  <text x="50" y="168" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">-3</text>
  <text x="116.6" y="168" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">-2</text>
  <text x="183.3" y="168" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">-1</text>
  <text x="256" y="168" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="start">0</text>
  <text x="316.6" y="168" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">1</text>
  <text x="383.3" y="168" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">2</text>
  <text x="450" y="168" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">3</text>
  <text x="240" y="254" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="end">-1.0</text>
  <text x="240" y="204" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="end">-0.5</text>
  <text x="240" y="104" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="end">0.5</text>
  <text x="240" y="54" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="end">1.0</text>
</svg>

---

### ReLU (Rectified Linear Unit)

**Paper**: *Rectified Linear Units Improve Restricted Boltzmann Machines* by Vinod Nair and Geoffrey Hinton, 2010.

Both Sigmoid and Tanh suffer from the "vanishing gradient" problem: for very high or low values of $z$, the curve goes completely flat, killing the gradient signal needed to train deep networks.
ReLU became the gold standard after its use in the breakthrough 2012 **AlexNet** model. Because its derivative is a constant 1 for all positive inputs, it allows gradients to flow strongly through dozens of layers,
enabling modern Deep Learning.

**Mathematical Definition:**
$$\text{ReLU}(z) = \max(0, z)$$

**Derivative:**
The derivative of ReLU is incredibly simple, making it highly computationally efficient. Note that strictly speaking, the derivative is undefined exactly at $z=0$,
but in software implementations (like PyTorch or TensorFlow), it is arbitrarily assigned a value of 0.
$$
\text{ReLU}'(z) = \begin{cases} 
1 & \text{if } z > 0 \\\\ 
0 & \text{if } z < 0 
\end{cases}
$$

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 500 300" style="width: 100%; height: auto; max-width: 500px; display: block; margin: 1.5rem auto; background-color: #ffffff; border-radius: 8px; border: 1px solid #e2e8f0;">
  <defs>
    <marker id="arrow-relu" markerWidth="10" markerHeight="10" refX="9" refY="3" orient="auto">
      <path d="M0,0 L0,6 L9,3 z" fill="#64748b" />
    </marker>
  </defs>
  <g stroke="#f1f5f9" stroke-width="1">
    <line x1="50" y1="50" x2="450" y2="50" />
    <line x1="50" y1="100" x2="450" y2="100" />
    <line x1="50" y1="150" x2="450" y2="150" />
    <line x1="50" y1="200" x2="450" y2="200" />
    <line x1="100" y1="30" x2="100" y2="270" />
    <line x1="175" y1="30" x2="175" y2="270" />
    <line x1="325" y1="30" x2="325" y2="270" />
    <line x1="400" y1="30" x2="400" y2="270" />
  </g>
  <line x1="50" y1="250" x2="450" y2="250" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-relu)" />
  <line x1="250" y1="280" x2="250" y2="20" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-relu)" />
  <path d="M 50,249 L 250,249 L 430,69" fill="none" stroke="#10b981" stroke-width="4" stroke-linejoin="round" />
  <text x="230" y="265" font-family="sans-serif" font-size="12" fill="#64748b">0</text>
  <text x="440" y="240" font-family="sans-serif" font-size="12" fill="#64748b">z</text>
</svg>

---

### Leaky ReLU

**Paper**: *Rectifier Nonlinearities Improve Neural Network Acoustic Models* by Andrew L. Maas, Awni Y. Hannun, and Andrew Y. Ng, 2013.

While ReLU is incredibly effective, it suffers from the "Dying ReLU" problem: if a large gradient updates a weight such that the neuron's input is always negative, that neuron will forever output 0.
Because the gradient at 0 is also 0, it can never recover. Leaky ReLU solves this by allowing a small, non-zero gradient when the unit is inactive, keeping the neurons "alive" and updating.

**Mathematical Definition:**
$$\text{LeakyReLU}(z) = \begin{cases} z & \text{if } z > 0 \\\\ \alpha z & \text{if } z \le 0 \end{cases}$$
*(Where $\alpha$ is a small constant, typically 0.01).*

**Derivative:**
The derivative is trivial to compute, ensuring the computational efficiency of standard ReLU is maintained while preventing dead neurons.
$$
\text{LeakyReLU}'(z) = \begin{cases} 
1 & \text{if } z > 0 \\\\ 
\alpha & \text{if } z < 0 
\end{cases}
$$

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 500 300" style="width: 100%; height: auto; max-width: 500px; display: block; margin: 1.5rem auto; background-color: #ffffff; border-radius: 8px; border: 1px solid #e2e8f0;">
  <defs>
    <marker id="arrow-lrelu" markerWidth="10" markerHeight="10" refX="9" refY="3" orient="auto">
      <path d="M0,0 L0,6 L9,3 z" fill="#64748b" />
    </marker>
  </defs>
  <g stroke="#f1f5f9" stroke-width="1">
    <line x1="50" y1="50" x2="450" y2="50" />
    <line x1="50" y1="100" x2="450" y2="100" />
    <line x1="50" y1="150" x2="450" y2="150" />
    <line x1="50" y1="200" x2="450" y2="200" />
    <line x1="100" y1="30" x2="100" y2="270" />
    <line x1="175" y1="30" x2="175" y2="270" />
    <line x1="325" y1="30" x2="325" y2="270" />
    <line x1="400" y1="30" x2="400" y2="270" />
  </g>
  <line x1="50" y1="250" x2="450" y2="250" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-lrelu)" />
  <line x1="250" y1="280" x2="250" y2="20" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-lrelu)" />
  <path d="M 50,275 L 250,249 L 430,69" fill="none" stroke="#f59e0b" stroke-width="4" stroke-linejoin="round" />
  <text x="230" y="240" font-family="sans-serif" font-size="12" fill="#64748b">0</text>
  <text x="440" y="240" font-family="sans-serif" font-size="12" fill="#64748b">z</text>
</svg>

---

### GELU (Gaussian Error Linear Unit)

**Paper**: *Gaussian Error Linear Units (GELUs)* by Dan Hendrycks and Kevin Gimpel, 2016.

As AI architecture shifted heavily towards Transformers (the architecture powering models like BERT, GPT, and modern LLMs), researchers discovered that weighting inputs by their probability within a
standard Gaussian distribution yielded better results. Unlike ReLU, GELU is a smooth, non-monotonic curve. It dips slightly below zero for small negative numbers before flattening out, essentially acting as a softer,
probabilistic version of dropout and activation combined.

**Mathematical Definition:**
$$\text{GELU}(z) = z \cdot \Phi(z)$$
*(Where $\Phi(z)$ is the cumulative distribution function for Gaussian distribution. This is frequently approximated in code as $0.5 z (1 + \tanh[\sqrt{2/\pi}(z + 0.044715 z^3)])$).*

**Derivative:**
The derivative relies on the Gaussian probability density function $\phi(z)$. The non-zero derivative for small negative values gives it a similar anti-dying property to Leaky ReLU, but strictly bounded and mathematically smooth.
$$
\text{GELU}'(z) = \Phi(z) + z \phi(z)
$$

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 500 300" style="width: 100%; height: auto; max-width: 500px; display: block; margin: 1.5rem auto; background-color: #ffffff; border-radius: 8px; border: 1px solid #e2e8f0;">
  <defs>
    <marker id="arrow-gelu" markerWidth="10" markerHeight="10" refX="9" refY="3" orient="auto">
      <path d="M0,0 L0,6 L9,3 z" fill="#64748b" />
    </marker>
  </defs>
  <g stroke="#f1f5f9" stroke-width="1">
    <line x1="50" y1="50" x2="450" y2="50" />
    <line x1="50" y1="100" x2="450" y2="100" />
    <line x1="50" y1="150" x2="450" y2="150" />
    <line x1="50" y1="200" x2="450" y2="200" />
    <line x1="100" y1="30" x2="100" y2="270" />
    <line x1="175" y1="30" x2="175" y2="270" />
    <line x1="325" y1="30" x2="325" y2="270" />
    <line x1="400" y1="30" x2="400" y2="270" />
  </g>
  <line x1="50" y1="250" x2="450" y2="250" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-gelu)" />
  <line x1="250" y1="280" x2="250" y2="20" stroke="#64748b" stroke-width="2" marker-end="url(#arrow-gelu)" />
  <path d="M 50,250 L 150,250 C 200,250 215,268 250,249 C 280,225 320,180 430,70" fill="none" stroke="#ec4899" stroke-width="4" stroke-linecap="round" />
  <text x="230" y="240" font-family="sans-serif" font-size="12" fill="#64748b">0</text>
  <text x="440" y="240" font-family="sans-serif" font-size="12" fill="#64748b">z</text>
</svg>
