+++
title = "Multi Layer Perceptrons"
date = 2026-05-01T22:32:51+05:45
tags = ["mlp", "deep-learning", "universal-approximation"]
description = "Understanding Multi-Layer Perceptrons, network depth, and their theoretical capabilities as universal function approximators."
+++


## Multi-Layer Perceptrons (MLPs)

An MLP is a network of individual perceptrons, organized into interconnected sequential layers. 

### Anatomy of an MLP
In a standard feedforward MLP, data flows strictly in one direction (from input to output) through the following structure:
1. **Input Layer**: The initial nodes that receive the raw data features. (Technically, these aren't "computing" neurons, just data placeholders).
2. **Hidden Layers**: All intermediate layers whose activations we don't directly see as the final answer. These layers act as internal feature extractors, learning increasingly complex representations of the data. 
3. **Output / Outer Layer**: The final layer whose computed output we actually observe and use for our prediction or classification.

### Defining "Depth" in Deep Networks

The term "Deep Learning" is thrown around constantly, but mathematically, what makes a network "deep"?

Using standard graph theory, the **depth** of a network is defined as the length of the longest path from a root node (the source or input) to a leaf node (the sink or output).
- A single perceptron (Input -> Output) has a depth of 1.
- A network with one hidden layer (Input -> Hidden -> Output) has a depth of 2.

In deep learning literature, a network is formally considered **"Deep" if its depth is strictly greater than 2**. Therefore, a deep neural network must have at least 3 layers (e.g., an Input layer, at least two Hidden layers, and an Output layer). Depth means the number of layers with trainable parameters.

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 400" style="width: 100%; height: auto; max-width: 800px; display: block; margin: 1.5rem auto; background-color: #f8fafc; border-radius: 8px; border: 1px solid #e2e8f0;">
  <g stroke="#cbd5e1" stroke-width="1.5">
    <line x1="100" y1="100" x2="300" y2="70" /> <line x1="100" y1="100" x2="300" y2="150" /> <line x1="100" y1="100" x2="300" y2="230" /> <line x1="100" y1="100" x2="300" y2="310" />
    <line x1="100" y1="200" x2="300" y2="70" /> <line x1="100" y1="200" x2="300" y2="150" /> <line x1="100" y1="200" x2="300" y2="230" /> <line x1="100" y1="200" x2="300" y2="310" />
    <line x1="100" y1="300" x2="300" y2="70" /> <line x1="100" y1="300" x2="300" y2="150" /> <line x1="100" y1="300" x2="300" y2="230" /> <line x1="100" y1="300" x2="300" y2="310" />
    <line x1="300" y1="70" x2="500" y2="70" /> <line x1="300" y1="70" x2="500" y2="150" /> <line x1="300" y1="70" x2="500" y2="230" /> <line x1="300" y1="70" x2="500" y2="310" />
    <line x1="300" y1="150" x2="500" y2="70" /> <line x1="300" y1="150" x2="500" y2="150" /> <line x1="300" y1="150" x2="500" y2="230" /> <line x1="300" y1="150" x2="500" y2="310" />
    <line x1="300" y1="230" x2="500" y2="70" /> <line x1="300" y1="230" x2="500" y2="150" /> <line x1="300" y1="230" x2="500" y2="230" /> <line x1="300" y1="230" x2="500" y2="310" />
    <line x1="300" y1="310" x2="500" y2="70" /> <line x1="300" y1="310" x2="500" y2="150" /> <line x1="300" y1="310" x2="500" y2="230" /> <line x1="300" y1="310" x2="500" y2="310" />
    <line x1="500" y1="70" x2="700" y2="150" /> <line x1="500" y1="70" x2="700" y2="250" />
    <line x1="500" y1="150" x2="700" y2="150" /> <line x1="500" y1="150" x2="700" y2="250" />
    <line x1="500" y1="230" x2="700" y2="150" /> <line x1="500" y1="230" x2="700" y2="250" />
    <line x1="500" y1="310" x2="700" y2="150" /> <line x1="500" y1="310" x2="700" y2="250" />
  </g>
  <g stroke-width="3">
    <g fill="#fee2e2" stroke="#ef4444">
      <circle cx="100" cy="100" r="22" /> <circle cx="100" cy="200" r="22" /> <circle cx="100" cy="300" r="22" />
    </g>
    <g fill="#eff6ff" stroke="#3b82f6">
      <circle cx="300" cy="70" r="22" /> <circle cx="300" cy="150" r="22" /> <circle cx="300" cy="230" r="22" /> <circle cx="300" cy="310" r="22" />
    </g>
    <g fill="#eff6ff" stroke="#3b82f6">
      <circle cx="500" cy="70" r="22" /> <circle cx="500" cy="150" r="22" /> <circle cx="500" cy="230" r="22" /> <circle cx="500" cy="310" r="22" />
    </g>
    <g fill="#f0fdf4" stroke="#22c55e">
      <circle cx="700" cy="150" r="22" /> <circle cx="700" cy="250" r="22" />
    </g>
  </g>
  <g font-family="sans-serif" font-size="14" font-weight="bold" fill="#334155" text-anchor="middle">
    <text x="100" y="35">Input Layer</text>
    <text x="300" y="35">Hidden Layer 1</text>
    <text x="500" y="35">Hidden Layer 2</text>
    <text x="700" y="35">Output Layer</text>
  </g>
  <path d="M 300,350 L 300,360 L 700,360 L 700,350" fill="none" stroke="#64748b" stroke-width="2" />
  <text x="500" y="380" font-family="sans-serif" font-size="14" fill="#64748b" text-anchor="middle">Depth &gt; 2 = "Deep Network"</text>
</svg>

## MLPs Approximate Functions

If we view a neural network mathematically, it is simply a massive composite function. You feed an input vector $X$ into the network, and it spits out an output vector $Y$. The remarkable thing about MLPs is the variety and complexity of functions they can emulate:

1. **Boolean Functions**: Just as Minsky and Papert proved that a 2-layer network can solve `XOR`, an MLP can perfectly compose and solve any complex boolean logic gate array.
2. **Classification Boundaries**: By chaining together multiple affine transformations and non-linear activations, MLPs can draw highly complex, non-linear decision boundaries around data clusters in multi-dimensional space.
3. **Real-Valued Functions**: Most importantly, MLPs can approximate continuous mathematical functions, mapping inputs to precise numerical outputs.

This leads us to one of the most famous theorems in artificial intelligence.

### The Universal Approximation Theorem

The **Universal Approximation Theorem** was first proven for sigmoid activation functions by George Cybenko, and later generalized to multilayer architectures and other activations by Kurt Hornik.

**Key Papers:**
- *Cybenko, G. (1989).* "Approximation by superpositions of a sigmoidal function"
- *Hornik, K. (1991).* "Approximation capabilities of multilayer feedforward networks"

The theorem makes a profound guarantee:
> A feedforward network with a linear output layer and at least one hidden layer containing a finite number of neurons (using a non-linear activation function) can approximate any continuous function on a compact subset of $\mathbb{R}^n$ to an arbitrary degree of precision.

In plain English: **No matter how complex the relationship is between your inputs and outputs, there exists an MLP that can model it.** You do not even need a "deep" network. The theorem proves that a shallow network with a depth of 2 (just one hidden layer) is theoretically sufficient, provided that layer is wide enough.

### What are the Limitations?

If a shallow network can theoretically learn *any* function, why do we bother building deep networks, and why doesn't machine learning perfectly solve every problem immediately? 

The theorem is an existence proof—it guarantees the optimal network *exists*, but it doesn't guarantee that we can easily find it. The limitations lie in practical execution:

1. **Exponential Width**: To approximate highly complex functions with only a single hidden layer, the number of neurons required in that layer scales exponentially. Deep networks are used because depth allows the network to compose hierarchical features (like edges $\rightarrow$ shapes $\rightarrow$ faces), which requires vastly fewer neurons than a single infinitely wide hidden layer.
2. **The Optimization Problem**: Just because the perfect weights exist doesn't mean our training algorithm (like Gradient Descent) will find them. Training can easily fail due to vanishing gradients, getting stuck in local minima, or navigating poor loss landscapes.
3. **Generalization vs. Memorization**: The theorem guarantees the network can perfectly map the training data you provide. However, it does not guarantee that the network will generalize well to *unseen* data. A network with immense capacity might simply memorize the noise in your dataset (overfitting).
4. **Data Availability**: To accurately carve out the exact continuous function in a high-dimensional space, you need enough sample data to anchor the curve. We often lack sufficient data to approximate the function perfectly.

---

## How MLPs Model Functions: Classification vs. Regression

If we view a neural network mathematically, it is simply a massive composite function. You feed an input vector $X$ into the network, and it spits out an output vector $Y$. But how does it physically map out these solutions?

### 1. Classification (Creating Boundaries)
In classification, the network's goal is to draw a boundary between different clusters of data. 
* When using piecewise linear activations (like **ReLU** or step functions), the network constructs jagged, intersecting hyperplanes—acting almost like a geodesic dome wrapping around the data.
* When using continuous, smooth activations (like **Tanh** or **Sigmoid**), the network constructs fluid, wavy, smooth boundaries that elegantly curve around the data clusters.

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 850 350" style="width: 100%; height: auto; max-width: 850px; display: block; margin: 1.5rem auto; background-color: #ffffff; border-radius: 8px; border: 1px solid #e2e8f0;">
  <g transform="translate(50, 50)">
    <rect width="300" height="250" fill="#f8fafc" stroke="#cbd5e1" stroke-width="2"/>
    <text x="150" y="-15" font-family="sans-serif" font-size="16" font-weight="bold" fill="#334155" text-anchor="middle">Piecewise Boundary (e.g., ReLU)</text>
    <circle cx="80" cy="80" r="6" fill="#3b82f6"/><circle cx="110" cy="60" r="6" fill="#3b82f6"/><circle cx="140" cy="90" r="6" fill="#3b82f6"/><circle cx="90" cy="120" r="6" fill="#3b82f6"/>
    <circle cx="220" cy="180" r="6" fill="#ef4444"/><circle cx="180" cy="210" r="6" fill="#ef4444"/><circle cx="250" cy="200" r="6" fill="#ef4444"/><circle cx="210" cy="230" r="6" fill="#ef4444"/>
    <polyline points="0,180 120,160 180,100 240,0" fill="none" stroke="#1e293b" stroke-width="3" stroke-dasharray="6"/>
  </g>
  <g transform="translate(450, 50)">
    <rect width="300" height="250" fill="#f8fafc" stroke="#cbd5e1" stroke-width="2"/>
    <text x="150" y="-15" font-family="sans-serif" font-size="16" font-weight="bold" fill="#334155" text-anchor="middle">Smooth Boundary (e.g., Tanh)</text>
    <circle cx="80" cy="80" r="6" fill="#3b82f6"/><circle cx="110" cy="60" r="6" fill="#3b82f6"/><circle cx="140" cy="90" r="6" fill="#3b82f6"/><circle cx="90" cy="120" r="6" fill="#3b82f6"/>
    <circle cx="220" cy="180" r="6" fill="#ef4444"/><circle cx="180" cy="210" r="6" fill="#ef4444"/><circle cx="250" cy="200" r="6" fill="#ef4444"/><circle cx="210" cy="230" r="6" fill="#ef4444"/>
    <path d="M 0,200 C 100,200 120,120 180,100 C 240,80 270,40 300,0" fill="none" stroke="#1e293b" stroke-width="3"/>
  </g>
</svg>

### 2. Regression (Predicting Real Values)
If we want to predict a continuous numerical curve (like a stock price over time), the Universal Approximation Theorem acts like a massive set of Lego blocks. We can visualize this clearly by looking at how a network builds a simple "square pulse."

To approximate a highly complex, wavy continuous function, the network simply chains together hundreds of these isolated blocks side-by-side, adjusting the height of each pulse. If we use enough neurons to make the individual pulses incredibly narrow, the jagged stairs perfectly blur into a smooth, arbitrary curve.

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 850 400" style="width: 100%; height: auto; max-width: 850px; display: block; margin: 1.5rem auto; background-color: #ffffff; border-radius: 8px; border: 1px solid #e2e8f0;">
  <defs>
    <marker id="arrow" markerWidth="10" markerHeight="10" refX="9" refY="3" orient="auto">
      <path d="M0,0 L0,6 L9,3 z" fill="#64748b" />
    </marker>
  </defs>
  <g transform="translate(20, 60)">
    <rect width="360" height="300" fill="#f8fafc" stroke="#cbd5e1" stroke-width="1.5" rx="10"/>
    <text x="180" y="-20" font-family="sans-serif" font-size="16" font-weight="bold" fill="#334155" text-anchor="middle">Building a "Square Pulse"</text>
    <circle cx="40" cy="150" r="18" fill="#e2e8f0" stroke="#94a3b8" stroke-width="2"/>
    <text x="40" y="155" font-family="sans-serif" font-size="16" font-weight="bold" text-anchor="middle">X</text>
    <g transform="translate(140, 85)">
      <circle cx="0" cy="0" r="22" fill="#fff" stroke="#334155" stroke-width="2"/>
      <text x="0" y="5" font-family="sans-serif" font-size="14" font-weight="bold" text-anchor="middle">T₁</text>
      <path d="M -30,-45 L -10,-45 L -10,-65 L 15,-65" fill="none" stroke="#ef4444" stroke-width="2"/>
      <line x1="-30" y1="-55" x2="15" y2="-55" stroke="#cbd5e1" stroke-width="1"/>
    </g>
    <g transform="translate(160, 210)">
      <circle cx="0" cy="0" r="22" fill="#fff" stroke="#334155" stroke-width="2"/>
      <text x="0" y="5" font-family="sans-serif" font-size="14" font-weight="bold" text-anchor="middle">T₂</text>
      <path d="M -30,65 L -10,65 L -10,45 L 15,45" fill="none" stroke="#ef4444" stroke-width="2"/>
      <line x1="-30" y1="55" x2="15" y2="55" stroke="#cbd5e1" stroke-width="1"/>
    </g>
    <circle cx="280" cy="150" r="20" fill="#f1f5f9" stroke="#334155" stroke-width="2"/>
    <g transform="translate(325, 150)">
      <path d="M -15,10 L -5,10 L -5,-10 L 5,-10 L 5,10 L 15,10" fill="none" stroke="#ef4444" stroke-width="2"/>
      <text x="0" y="-20" font-family="sans-serif" font-size="14" font-weight="bold" fill="#334155" text-anchor="middle">f(x)</text>
    </g>
    <g stroke="#64748b" stroke-width="1.5" marker-end="url(#arrow)">
      <line x1="60" y1="140" x2="115" y2="95" />
      <line x1="60" y1="160" x2="135" y2="210" />
      <line x1="165" y1="90" x2="255" y2="140" />
      <line x1="185" y1="210" x2="255" y2="155" />
    </g>
    <text x="75" y="110" font-family="sans-serif" font-size="14" fill="#334155">1</text>
    <text x="75" y="200" font-family="sans-serif" font-size="14" fill="#334155">1</text>
    <text x="210" y="110" font-family="sans-serif" font-size="14" fill="#334155">1</text>
    <text x="210" y="210" font-family="sans-serif" font-size="14" fill="#ef4444">-1</text>
  </g>
  <g transform="translate(420, 60)">
    <rect width="400" height="300" fill="#ffffff" stroke="#cbd5e1" stroke-width="1.5" rx="10"/>
    <text x="200" y="-20" font-family="sans-serif" font-size="16" font-weight="bold" fill="#334155" text-anchor="middle">Approximating Arbitrary Curves</text>
    <line x1="30" y1="260" x2="370" y2="260" stroke="#94a3b8" stroke-width="1.5" marker-end="url(#arrow)"/>
    <line x1="50" y1="280" x2="50" y2="20" stroke="#94a3b8" stroke-width="1.5" marker-end="url(#arrow)"/>
    <g fill="#fee2e2" stroke="#ef4444" stroke-width="1">
      <rect x="50" y="160" width="25" height="100" />
      <rect x="75" y="130" width="25" height="130" />
      <rect x="100" y="90" width="25" height="170" />
      <rect x="125" y="110" width="25" height="150" />
      <rect x="150" y="180" width="25" height="80" />
      <rect x="175" y="210" width="25" height="50" />
      <rect x="200" y="140" width="25" height="120" />
      <rect x="225" y="80" width="25" height="180" />
      <rect x="250" y="100" width="25" height="160" />
      <rect x="275" y="160" width="25" height="100" />
      <rect x="300" y="220" width="25" height="40" />
      <rect x="325" y="180" width="25" height="80" />
    </g>
    <path d="M 50,160 C 80,100 120,50 150,180 C 180,260 210,140 240,80 C 270,40 320,200 350,180" fill="none" stroke="#2563eb" stroke-width="3" stroke-linecap="round"/>
  </g>
</svg>

---

## The Network as a Function

When we think of network as a function, what it means is that the network is actually a universal map from the entire domain of individual values to the entire range of the output activation function.
So if output activation is sigmoid, it means output can only lie between 0 and 1. This means if we decide the output activation is sigmoid, then we can compose an MLP that can model any function from
a input space to the domain which lies between 0 and 1.

The MLP is a Universal Approximator for the entire class of functions (maps) it represents. where it represents a class of functions from some domain to some range or some co-domain.

---

## Network Capacity and Architecture Sufficiency

Even though an MLP *can* approximate a function, it must possess sufficient structural "capacity" to do so. If the architecture is too small, it fundamentally cannot represent a highly complex pattern exactly. 

For example, a specific classification pattern might require a minimum of 16 neurons in a single hidden layer to be captured perfectly. If you restrict that layer to fewer than 16 neurons, the network will fail to represent the pattern. Even if you add a second layer, if the first layer is bottlenecked (e.g., still having fewer than 16 neurons), the second layer would require a significantly larger number of neurons (e.g., 41 or more) just to compensate for the lost information. 

> **A Note on Scaling Capacity:** > How exactly do we measure this "capacity" as networks grow? In the 2017 paper *"A Capacity Scaling Law for Artificial Neural Networks"* by Gerald Friedland and Mario Krell, the authors derived two critical dimensions to predict perceptron network behavior: the lossless memory (LM) dimension and the MacKay (MK) dimension. Their crucial finding was that the capacity of a neural network scales **strictly linearly** with the total number of weights (parameters) in the network, establishing a hard mathematical upper bound on how much information a network can perfectly memorize and map.

---

## Information Flow: Width, Depth, and Activation Functions

The choice of activation function directly dictates how information survives as it flows through the network, especially when dealing with narrow hidden layers.

* **Threshold Activations (Hard Gates):** A rigid threshold activation acts like a closed door. It either passes the information forward or it completely gates (blocks) it. If a narrow layer uses threshold activations, any information that fails to trigger the threshold is permanently lost and cannot be recovered by deeper layers.
* **Continuous/Graded Activations:** Functions like Sigmoid, Tanh, or ReLU produce a *graded* output. Instead of a hard block, they allow "missed" or partial information to trickle through to subsequent layers. 

Because graded activations do not strictly destroy information, you can get away with using narrower layers (fewer neurons per layer). However, because the information is squeezed and diluted, the network requires **greater depth** (more layers) to fully process and untangle that graded information.

---

## Depth vs. Width: The Exponential Advantages of Deep Networks

If a shallow network can theoretically learn *any* function, why do we bother building deep networks? 

The Universal Approximation Theorem is an existence proof—it guarantees the optimal network *exists*, but it glosses over *efficiency*. Recent mathematical research has proven that depth provides an **exponential advantage in representational capacity**. Specifically, for piecewise linear activation functions like ReLU, adding depth increases the number of linear regions (how many ways the network can slice and fold the input space) exponentially, whereas adding width only increases it polynomially.

**Key Papers on Optimal Depth:**
- *Eldan, R., & Shamir, O. (2016).* "The Power of Depth for Feedforward Neural Networks"
- *Telgarsky, M. (2016).* "Benefits of depth in neural networks"

### The Sawtooth Example
To see this exponential advantage in action, let's look at an explicit mathematical example adapted from Matus Telgarsky's paper. 

Assume we have a **1-dimensional input** ($x \in \mathbb{R}$) and we want the network to model a highly oscillating function—specifically, a "sawtooth" wave with $1024$ distinct teeth (linear segments).

**1. The Shallow Network (Without Optimal Depth):**
In a shallow network with only 1 hidden layer, each ReLU neuron acts like a single hinge or "fold" in the function. To create a function with 1024 distinct teeth, you must explicitly encode each fold. 
- You need exactly $1024$ independent neurons in that single hidden layer.
- **Total required neurons:** $1024$

**2. The Deep Network (With Optimal Depth):**
Now consider a deep network. A single hidden layer of just 2 ReLU neurons can be configured to compute a simple triangle wave (1 tooth). If you feed that triangle wave into *another* layer of 2 ReLU neurons, the function folds over itself, producing 2 teeth. Feed it into another layer, and it folds again, producing 4 teeth.

Because of function composition ($f(f(f(x)))$), stacking layers doubles the number of teeth at every step. To get $2^{10} = 1024$ teeth, we only need to stack $10$ layers, each containing just 2 neurons.
- We need 10 layers $\times$ 2 neurons per layer.
- **Total required neurons:** $20$

**The Conclusion:** To approximate the exact same function, a shallow network required **1024 neurons**, while a deep network required only **20 neurons**. If we wanted $1,048,576$ teeth ($2^{20}$), the shallow network would need over a million neurons, while the deep network would need only 40. 

If optimal depth is not achieved, the number of required perceptrons (the width) scales exponentially with the complexity of the function. Achieving optimal depth allows the network size to decrease exponentially, unlocking immense computational efficiency.

{{< callout type="tip" title="What about Smooth Functions like Sigmoid and Tanh?" >}}
The sawtooth example above relies on **ReLU** because its piecewise linear nature makes "folds" or "teeth" easy to explicitly count. But does this exponential advantage apply to smooth, continuously differentiable functions like **Sigmoid** or **Tanh**? 

**Yes!** However, instead of counting flat linear regions, mathematicians measure the expressivity of smooth networks by counting **oscillations**, **inflection points**, or **roots** (how many times the curve crosses zero). Just as stacking ReLU layers multiplies sharp folds, stacking layers of `tanh` multiplies these smooth oscillations. A deep `tanh` network can weave an exponentially complex, highly oscillating curve using very few neurons, whereas a wide, shallow `tanh` network would require exponentially more neurons to force the same wavy complexity.
{{< /callout >}}

---

## Feature Independence and The Curse of Dimensionality

A common misconception is that the number of neurons needed in a network grows exponentially with the raw number of input features (e.g., a 100x100 pixel image having 10,000 features). Mathematically, approximating a general function in high dimensions requires an exponentially large grid. This is known as the **Curse of Dimensionality**.

{{< callout type="tip" title="Why do dimensions cause exponential growth?" >}}
To understand the curse, imagine trying to map out temperature by placing a sensor every 1 meter.
* **1D Space (A 10m hallway):** You need **10 sensors**. 
* **2D Space (A 10x10m room):** You need $10 \times 10 =$ **100 sensors**.
* **3D Space (A 10x10x10m room):** You need $10 \times 10 \times 10 =$ **1,000 sensors**.

Notice how the number of sensors needed to cover the space grows exponentially ($10^N$) as the number of dimensions ($N$) increases. If a neural network tries to learn a random, chaotic function across a 100-dimensional space, the volume is so massive that the number of perceptrons needed to "cover" all distinct regions blows up.
{{< /callout >}}

However, the number of perceptrons actually required grows exponentially *only with the number of statistically independent features*—often referred to as the data's "intrinsic dimensionality" or the **Manifold Hypothesis**.

**Key Paper:**
- *Poggio, T., Liao, Q., et al. (2017).* "Why and when can deep-but not shallow-networks avoid the curse of dimensionality"

### The Sensor Example
Imagine a small room with 100 temperature sensors scattered around it. You feed all 100 sensor readings (100 raw features) into an MLP to predict the room's overall climate. 

Because the sensors are close together, their readings are highly correlated. If a window opens, 50 sensors drop in temperature simultaneously. These features are **not statistically independent**. The entire room's temperature might truly be governed by only 2 independent factors: (1) Is the heater on? (2) Is the window open?

{{< callout type="note" title="What is a 'Manifold'?" >}}
A manifold is simply a lower-dimensional shape embedded inside a higher-dimensional space. 

Think of a flat, 2D sheet of paper. You only need 2 coordinates (X, Y) to find a point on it. If you crumple that paper and toss it into your 3D bedroom, you now technically need 3 coordinates (X, Y, Z) to locate the point in the room. However, the paper itself is still fundamentally a 2D surface—just warped and folded. **That crumpled paper is a 2D manifold living in a 3D space.**
{{< /callout >}}

The data from our sensors actually lies on a simple 2-dimensional manifold within a 100-dimensional space. When you feed this 100-dimensional vector into an MLP, the early layers of the network essentially "untwist" the crumpled paper, and the later layers learn the function on the flat 2D sheet. 

Because the network only has to learn a 2-dimensional space, the required size of the neural network scales exponentially with the *intrinsic features* ($2^2$), not the raw inputs ($2^{100}$). If all 100 sensors were emitting perfectly independent, uncorrelated random noise, the network would instantly succumb to the curse of dimensionality, and the required perceptrons would skyrocket. Deep networks excel at naturally factoring these correlated hierarchies, bypassing the curse of dimensionality for real-world structured data like images, text, and audio.
