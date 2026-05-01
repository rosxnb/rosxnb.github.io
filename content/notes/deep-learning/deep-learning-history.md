+++
title = "Deep Learning History"
date = 2026-05-01T00:02:38+05:45
tags = ["associationism", "connectionist-framework", "hebbian-learning", "perceptron", "mlp", "hidden-layer"]
math = true
description = "The history of deep learning: from early cognitive models to modern neural networks."
+++

# Introduction

Neural networks originally began as computational models of the brain and, more broadly, as models of human cognition. 

Historically, the earliest model of cognition was associationism. Over time, this evolved into the connectionist model of the brain. Current artificial neural networks operate entirely as connectionist machines.

Multi-layer perceptrons (MLPs) are foundational connectionist computational models. While typically used as classification engines, MLPs are also capable of modeling continuous-valued functions.
Ultimately, the most interesting AI tasks are simply complex functions that can be approximated by these networks.

## Human Cognition

Cognition refers to the mental processes of acquiring, storing, retrieving, and using knowledge. This encompasses thinking, memory, perception, and problem-solving,
allowing us to reason, plan, make decisions, and comprehend the world around us.

The earliest attempts to understand human cognition date back to 600 BC. At around 400 BC, **Plato** introduced foundational theories of cognition that would later form the basis of the theory of associationism.

> Plato suggested that cognition is fundamentally based on forming associations.

---

### The Theory of Associationism

In simple terms, the theory posits:
> Our ability to think, recognize patterns, and act on those recognitions to draw inferences is entirely based on learned associations.

**For instance**: Lightning is usually followed by thunder. Upon observing this sequence, you form a mental association between lightning and thunder. Thereafter, if you see lightning, you expect to hear thunder;
conversely, if you hear thunder, you infer that lightning must have struck nearby.

Machine learning can be understood through this exact lens of associations. At its core, an algorithm learns to associate a specific input with a specific output. While these associations can become arbitrarily complex,
they remain associations nonetheless. Mathematical functions themselves are just formal associations.

**The idea of associations is insightful, yet somewhat incomplete**.  
Simply stating that we form associations doesn't explain the underlying mechanics. Even though the brain undeniably relies on these associations, critical questions remain:
- Where are these associations stored?
- How are they physically encoded?

---

To understand how associations are stored and inferences are made, we must look at the biological architecture of the human brain. By the mid-1800s, advancements in microscopy allowed scientists to examine brain slices,
leading to the discovery that the **brain is a massive network of interconnected neurons**.

However, understanding the physical structure of the brain was only the first step; scientists still needed a computational model to explain how it processed information.

## The Connectionist Framework: The First ANN Proposal

Modeling the brain was highly complex because the same biological organ performed a vast array of seemingly unrelated computational tasks.

The first computational model proposing how the brain operates was introduced in 1873 by **Alexander Bain** in his book *Mind and Body*. His core thesis was revolutionary for its time: **the information lies within the connections**.

**Bain's Key Ideas**:
- **Neural Groupings**: Information is stored in the structural connections and how individual units are networked together.
- **Making Memories**: Bain proposed a mechanism for how a brain could learn to form these connections:
    > "when two impressions concur, or closely succeed one another, the nerve-currents find some bridge or place of continuity, better or worse, according to the abundance of nerve matter available for the transition."
- Remarkably, Bain was predicting **Hebbian learning** decades before it was formally articulated.

## What Are the Units?

When modeling the brain, the fundamental unit of computation is the **neuron**.  
A biological neuron consists of:
- **Soma**: The main body of the cell.
- **Dentrites**: The branching structures that receive incoming signals from other neurons. If the cumulative incoming signal exceeds a certain threshold, the neuron activates (fires).
- **Axon**: When the neuron fires, the electrical signal travels down the axon, which branches out to connect with the dendrites of other neurons.

## Computational Models of the Neuron

Once the neuron was identified as the base unit, researchers required a formal mathematical model to simulate its behavior.

---

### The McCulloch and Pitts Model (1943)

**Paper**: *A Logical Calculus of the Ideas Immanent in Nervous Activity*, Bulletin of Mathematical Biophysics, 5:115-137, 1943.

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 800 300" style="width: 100%; height: auto; max-width: 800px; display: block; margin: 2rem auto;">
  <rect width="100%" height="100%" fill="#f1f3f0" rx="8" />
  <g stroke="black" stroke-width="3" fill="none" stroke-linecap="round" stroke-linejoin="round">
    <line x1="520" y1="150" x2="680" y2="150"/>
    <polygon points="348,150 520,80 520,220" fill="#ffffff"/>
    <ellipse cx="358" cy="150" rx="8" ry="28" stroke-width="3"/>
    <path d="M 60,265 C 250,255 330,235 358,178"/>
    <path d="M 250,48 Q 440,60 460,103"/>
    <path d="M 100,29 Q 390,60 420,119"/>
  </g>
  <circle cx="420" cy="119" r="7" fill="black" />
  <circle cx="460" cy="103" r="7" fill="black" />
  <g>
    <rect x="580" y="40" width="180" height="40" fill="#fce938" stroke="black" stroke-width="1.5"/>
    <text x="592" y="66" font-family="'Comic Sans MS', 'Chalkboard SE', 'Marker Felt', sans-serif" font-size="20" fill="black">A single neuron</text>
  </g>
</svg>

The figure above illustrates the mathematical representation of a neuron as defined by Warren McCulloch and Walter Pitts.  
In this model, a neuron receives inputs through **excitatory synapses**. If the total signal coming down these connections exceeds a specific threshold, the neuron will fire.
However, if any signal arrives via an **inhibitory synapse** (represented by the lower connection with a ring attached), it acts as an absolute veto, preventing the neuron from firing regardless of the excitatory inputs.

Even this highly simplified model was proven capable of computing a wide variety of Boolean logic functions.

**Criticisms of the McCulloch-Pitts Model**:
- They claimed their networks could compute a small class of functions, and that if provided with external memory (like a tape), their nets would be equivalent to Turing machines. This claim of Turing completeness was highly debated.
- They did not mathematically prove their own claims.
- Most importantly, the model lacked a **learning mechanism**; there was no way for the network to automatically adjust its connections to learn specific operations.

---

### Donald Hebb and Hebbian Learning (1949)

**Book**: *The Organization of Behavior: A Neuropsychological Theory*, 1949.

**Hebbian Learning** provided the missing mechanism for neural adaptation:  
> "When an axon of cell A is near enough to excite a cell B and repeatedly or persistently takes part in firing it, some growth process or metabolic change takes place in one or both cells such that
A's efficiency, as one of the cells firing B, is increased."

Often summarized simply as: **"Neurons that fire together, wire together."**

If neuron $x_i$ repeatedly triggers neuron $y$, the synaptic connection between them strengthens. In mathematical terms, the weight ($w_i$) of the $i^{th}$ neuron's input to the output neuron $y$ updates as follows:

$$
w_i = w_i + \eta x_i y
$$

Numerous later modifications to basic Hebbian Learning introduced concepts like weight normalization and forgetting. For example, Generalized Hebbian Learning (also known as **Sanger's rule**)
distributes the contribution of an input incrementally over multiple outputs:

$$
w_{ij} = w_{ij} + \eta y_j \left( x_i - \sum_{k=1}^{j} w_{ik} y_k  \right)
$$

This conceptual formula forms the bedrock of many modern machine learning algorithms.

{{< callout type="warning" title="The Flaw in Basic Hebbian Learning" >}}
In its purest form, Hebbian learning is unstable because connections only ever strengthen. Since the weights never decrease and there is no mechanism for "competition" between synapses,
a network using strict Hebbian learning would eventually saturate, with every neuron firing constantly.
{{< /callout >}}

---

### Frank Rosenblatt: The Perceptron (1958)

**Paper**: *The Perceptron: A Probabilistic Model for Information Storage and Organization in the Brain*, 1958.

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 850 450" style="width: 100%; height: auto; max-width: 850px; display: block; margin: 2rem auto; border: 1px solid #e2e8f0; border-radius: 8px;">
  <defs>
    <marker id="arrowhead" markerWidth="10" markerHeight="7" refX="9" refY="3.5" orient="auto">
      <polygon points="0 0, 10 3.5, 0 7" fill="#334155" />
    </marker>
  </defs>
  <rect width="100%" height="100%" fill="#f8fafc" rx="8"/>
  <g font-family="sans-serif" font-size="18" fill="#1e293b" text-anchor="middle">
    <circle cx="150" cy="120" r="25" fill="#ffffff" stroke="#334155" stroke-width="2"/>
    <text x="150" y="126">x₁</text>
    <circle cx="150" cy="200" r="25" fill="#ffffff" stroke="#334155" stroke-width="2"/>
    <text x="150" y="206">x₂</text>
    <circle cx="150" cy="280" r="3" fill="#94a3b8"/>
    <circle cx="150" cy="295" r="3" fill="#94a3b8"/>
    <circle cx="150" cy="310" r="3" fill="#94a3b8"/>
    <circle cx="150" cy="380" r="25" fill="#ffffff" stroke="#334155" stroke-width="2"/>
    <text x="150" y="386">xₙ</text>
    <circle cx="450" cy="90" r="25" fill="#ffffff" stroke="#334155" stroke-width="2"/>
    <text x="450" y="96">1</text>
    <text x="450" y="55" font-size="16" fill="#64748b">Bias (x₀)</text>
  </g>
  <g stroke="#334155" stroke-width="2" marker-end="url(#arrowhead)">
    <line x1="175" y1="120" x2="355" y2="225"/>
    <line x1="175" y1="200" x2="350" y2="240"/>
    <line x1="175" y1="380" x2="355" y2="275"/>
    <line x1="450" y1="115" x2="450" y2="155"/>
  </g>
  <g font-family="sans-serif" font-size="16" fill="#b91c1c" font-weight="bold">
    <text x="240" y="160">w₁</text>
    <text x="245" y="215">w₂</text>
    <text x="240" y="340">wₙ</text>
    <text x="460" y="140">w₀ (b)</text>
  </g>
  <g>
    <circle cx="450" cy="250" r="80" fill="#ffffff" stroke="#334155" stroke-width="2"/>
    <line x1="450" y1="170" x2="450" y2="330" stroke="#334155" stroke-width="2"/>
    <text x="410" y="260" font-family="sans-serif" font-size="34" fill="#1e293b" text-anchor="middle">∑</text>
    <text x="410" y="290" font-family="sans-serif" font-size="12" fill="#64748b" text-anchor="middle">Σ xᵢwᵢ + b</text>
    <line x1="465" y1="250" x2="515" y2="250" stroke="#cbd5e1" stroke-width="1.5"/>
    <line x1="490" y1="215" x2="490" y2="285" stroke="#cbd5e1" stroke-width="1.5"/>
    <path d="M 465 265 L 490 265 L 490 235 L 515 235" fill="none" stroke="#2563eb" stroke-width="3"/>
  </g>
  <g stroke="#334155" stroke-width="2" marker-end="url(#arrowhead)">
    <line x1="530" y1="250" x2="680" y2="250"/>
  </g>
  <g font-family="sans-serif" fill="#1e293b">
    <text x="700" y="245" font-size="18" font-weight="bold">Output (y)</text>
    <text x="700" y="265" font-size="14" fill="#64748b">0 or 1</text>
  </g>
  <g font-family="sans-serif" font-size="15" fill="#64748b" font-weight="bold" text-anchor="middle">
    <text x="150" y="430">INPUTS</text>
    <text x="260" y="430">WEIGHTS</text>
    <text x="410" y="360">NET SUM</text>
    <text x="490" y="360">ACTIVATION</text>
  </g>
</svg>

Rosenblatt's Perceptron improved upon the Hebbian learning method by introducing a mathematically robust architecture:

- Multiple inputs are combined linearly.
- **Threshold logic**: The neuron fires if the weighted sum of inputs exceeds a specific threshold.

$$
Y = \begin{cases} 
1 & \text{if } \sum_{i} w_i x_i - T > 0 \\\\ 
0 & \text{else} 
\end{cases}
$$

Rosenblatt also formalized a supervised learning algorithm. The core idea was: to teach a perceptron a specific function, provide it with continuous examples of input-output pairs.
Because the output is Boolean (it either fires or it doesn't), the algorithm scales the weights by the difference between the desired output and the actual output.

$$
w = w + \eta (d(x) - y(x)) x
$$

In this Sequential Learning equation:
- $d(x)$ is the desired target output for input $x$.
- $y(x)$ is the actual output produced by the perceptron.

The perceptron updates its weights whenever it makes a mistake, and Rosenblatt mathematically proved that this algorithm would successfully converge for any linearly separable dataset.

---

### Minsky and Papert: Perceptrons Expanded (1969)

**Book**: *Perceptrons: An Introduction to Computational Geometry*, 1969 (Expanded Edition 1972).

While the Perceptron was a massive leap forward, Marvin Minsky and Seymour Papert demonstrated a critical limitation in 1969: a single-layer perceptron could not model the `XOR` (Exclusive OR) Boolean gate. 

Because of this limitation, individual perceptrons were considered weak computational elements. To solve non-linearly separable problems like `XOR`, interconnected *networks* of elements were strictly required.

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 900 550" style="width: 100%; height: auto; max-width: 900px; display: block; margin: 2rem auto; background-color: #f4f4f5; border-radius: 8px;">
  <defs>
    <marker id="arrowhead" markerWidth="10" markerHeight="7" refX="9" refY="3.5" orient="auto">
      <polygon points="0 0, 10 3.5, 0 7" fill="#1e293b" />
    </marker>
    <marker id="red-arrow" markerWidth="10" markerHeight="7" refX="9" refY="3.5" orient="auto">
      <polygon points="0 0, 10 3.5, 0 7" fill="#dc2626" />
    </marker>
  </defs>
  <g stroke="#1e293b" stroke-width="2.5" marker-end="url(#arrowhead)">
    <line x1="140" y1="110" x2="355" y2="185"/>
    <line x1="140" y1="120" x2="360" y2="335"/>
    <line x1="140" y1="430" x2="360" y2="215"/>
    <line x1="140" y1="440" x2="355" y2="365"/>
    <line x1="455" y1="200" x2="655" y2="260"/>
    <line x1="455" y1="350" x2="655" y2="290"/>
    <line x1="745" y1="275" x2="795" y2="275"/>
  </g>
  <g fill="#fde047">
    <rect x="230" y="100" width="36" height="36" />  <rect x="250" y="220" width="36" height="36" />  <rect x="250" y="295" width="36" height="36" />  <rect x="230" y="405" width="36" height="36" />  <rect x="540" y="180" width="36" height="36" />  <rect x="540" y="320" width="36" height="36" />  </g>
  <g font-family="serif" font-size="20" fill="#dc2626" text-anchor="middle">
    <text x="248" y="125">1</text>
    <text x="268" y="245">-1</text>
    <text x="268" y="320">1</text>
    <text x="248" y="430">-1</text>
    <text x="558" y="205">1</text>
    <text x="558" y="345">1</text>
  </g>
  <g fill="#ffffff" stroke="#1e293b" stroke-width="3">
    <circle cx="400" cy="200" r="55"/>
    <circle cx="400" cy="350" r="55"/>
    <circle cx="700" cy="275" r="55"/>
  </g>
  <g fill="#fde047">
    <rect x="382" y="182" width="36" height="36" />
    <rect x="378" y="332" width="44" height="36" />
    <rect x="682" y="257" width="36" height="36" />
  </g>
  <g font-family="serif" font-size="20" fill="#dc2626" text-anchor="middle">
    <text x="400" y="207">1</text>
    <text x="400" y="357">-1</text>
    <text x="700" y="282">2</text>
  </g>
  <g font-family="serif" font-size="28" fill="#1e293b">
    <text x="100" y="120">X</text>
    <text x="100" y="450">Y</text>
    <text x="470" y="150">X ∨ Y</text>
    <text x="470" y="420"><tspan text-decoration="overline">X</tspan> ∨ <tspan text-decoration="overline">Y</tspan></text>
    <text x="810" y="283">X ⊕ Y</text>
  </g>
  <line x1="400" y1="480" x2="400" y2="420" stroke="#dc2626" stroke-width="2.5" marker-end="url(#red-arrow)"/>
  <rect x="320" y="485" width="160" height="40" fill="#e2e8f0" stroke="#cbd5e1" stroke-width="1" rx="4"/>
  <text x="400" y="512" font-family="sans-serif" font-size="18" fill="#334155" text-anchor="middle">Hidden Layer</text>
</svg>

#### Solving XOR with a Multi-Layer Network
To solve `XOR`, Minsky and Papert theorized the addition of a "hidden layer" between the inputs and the output:
- The top unit in the hidden layer performs $X \lor Y$ (OR).
- The bottom unit in the hidden layer performs $\neg X \lor \neg Y$ (NAND).
- The final output unit combines these signals, performing $(X \lor Y) \land (\neg X \lor \neg Y)$, which successfully models $X \oplus Y$ (XOR).
