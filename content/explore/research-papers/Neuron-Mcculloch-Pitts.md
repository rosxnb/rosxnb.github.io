+++
title = "Neuron Model by McCulloch and Pitts"
date = 2026-07-25T23:18:12+05:45
math = true
tags = ["neuron", "paper-review"]
description = "Neuron Model proposed by Mcculloch and Pitts in 1943."
+++

**Paper:** [A Logical Calculus of the Ideas Immanent In Nervous Activity, 1943, Warren S. McCulloch, Walter Pitts](https://home.csulb.edu/~cwallis/382/readings/482/mccolloch.logical.calculus.ideas.1943.pdf)

The first mathematical model of neuron was proposed by **Warren S. McCulloch** and **Walter Pitts** with following
assumptions about the Nervous System:

1. The activity of the neuron is an "**all-or-none**" process. A neuron either fires completely
   or doesn't fire at all. There is no such thing as "half-fire".

2. A fixed number of incoming connections (synapses) must be excited within the period of latent
   addition in order to excite a neuron. The required number doesn't change based on what the
   neuron did a moment ago or where the connections are located on the cell.

3. The only significant delay within the nervous system is synaptic delay.

   {{< fold summary="What is synaptic delay?" >}}
   Synaptic delay is the time gap between when a neuron fires and when that firing affects the next neuron.
   {{< /fold >}}

4. The activity of any inhibitory synapse absolutely prevents excitation of the neuron at that time.
   It acts like a strict "off switch".

   {{< fold summary="Global vs. local inhibition" >}}
   The paper acknowledges two possible ways inhibition could work in the brain:

   - **Chemical (Global):** A chemical is released that raises the neuron's threshold so high that
     it cannot activate.
   - **Physical (Local):** The inhibitory connection is placed in a specific physical spot that cancels
     out the incoming excitatory signals, like fighting a forward wave with a counter-wave.

   The paper chooses to go with the physical (local) inhibition because it doesn't require require
   inventing new hypothesis about special chemicals.
   {{< /fold >}}

5. The structure of the net does not change with the time.

   {{< fold summary="But nets do change — how do they get away with this?" >}}
   They do acknowledge that biological networks change in two ways:

   - Short-term changes: The neuron's sensitivity changes based on recent activity (getting tired or warmed up).
   - Long-term changes(Learning): The brain physically rewires itself based on experience.

   They tackle this problem by introducing a clever mathematical trick: **replacing time-varying components with a larger fixed network
   that reproduces the same behavior**. Instead of modelling a single neuron whose threshold changes over time, they imagine a
   "fictitious" network of multiple fixed-threshold neurons that act like a switchboard, routing signals to different part of the 
   circuit to mimic the changing state. Similarly, instead of modelling synapses that physically change through learning, they use
   separate fixed "learned" and "unlearned" pathways, with auxiliary circuitry that routes signals to the appropriate pathway based
   on the current state. This allows them to use unchanging, static math to model a dynamic, changing brain.
   {{< /fold >}}

By establishing these assumptions, like the "all-or-none" firing, synaptic delays, and inhibitory synapses, they are setting
up the pieces of their logical puzzle. A neuron becomes a logical proposition (True/False), and the synapses become the
logical operators (AND, OR, NOT).


## Key Notations and Definitions

- $N_i(t)$: Neuron $i$ fires at time $t$ (t measured in synaptic delays from time zero).

- $Pr$ or $P$: A predicate (True/False statement about a neuron firing at a given time).  
  Example: Given $P(t) = N_1(t) \land N_2(t)$, then $P(3)$ is true only if $N_1(t)$ and $N_2(t)$ both fire at time $t = 3$.

- $S$: Symbol for a unit time delay. $S(P)(t)$ means $P$ was true at time $t - 1$.  
  Verbally, if $N_A$ fired at time $t - 1$, then the signal will reach
  $N_B$ at time $t$ because of synaptic delay. The mathematical representation is done as:  
  $N_B(t) = S(N_A)(t) = N_A(t - 1)$.

- $S^2P$: $S(S(P))$ – two time delays.

- **Peripheral Afferents:** Neurons with no axons synapsing onto them (i.e., sensory input neurons, the one that receive
  external signals). All other neurons are internal.


## Key Insight

A neuron's firing at time $t$ depends ONLY on:

1. What other neurons fired at time $t -1$ (due to synaptic delay).
2. The threshold of that neuron.
3. Which synapses are excitatory vs inhibitory.

This gives us a direct mapping from neurons to logical formulas!

**How a Neuron Maps to Logic:**

For a neuron $c_i$ with:

- Threshold $\theta_i$ (e.g., needs 3 excitatory inputs).
- Excitatory synapses from neurons $c_{i1}, c_{i2}, ..., c_{ip}$ with multiplicities $n_{i1}, n_{i2}, ..., n_{ip}$.
- Inhibitory synapses from neurons $c_{j1}, c_{j2}, ..., c_{jq}$.

The firing rule becomes:

```text
Nᵢ(t) = S[
    (NOT Nⱼ₁(t−1)) · (NOT Nⱼ₂(t−1)) · ...
    AND
    (some combination of excitatory inputs sums to ≥ threshold)
]
```

Mathematical representation:

```math
N_i(t) \;=\; S\Big[\;
\underbrace{\neg N_{j1}(t-1) \land \neg N_{j2}(t-1) \land \cdots \land \neg N_{jq}(t-1)}_{\text{no inhibitor fired}}
\;\land\;
\underbrace{\Big(\sum_{k=1}^{p} n_{ik}\, N_{ik}(t-1) \;\ge\; \theta_i\Big)}_{\text{enough excitation}}
\;\Big]
```


## Temporal Propositional Expression (TPEs)

A TPE is any logical expression buld from:


1. Atomic propositions like $\phi(z)$ (where $z$ is a time variable).
2. Operations: $S$ (delay), $\lor$ (OR), $\land$ (AND), $\neg$ (NOT).


## Acyclic Net Theorems

Acyclic net are feed-forward only net. They have no feedback loop. They are also called Order-0 Net.

---

### Theorem 1: Every acyclic network is a TPE

> Any network without loops can be described by a temporal propositional expression.

**Reasoning:** You can start from the output neuron and "unroll" the network backward in time,
substituting each neuron's firing rule until you get an expression purely in terms of input neurons.
Since there are no cycles, this process terminates.

---

### Theorem 2: Every TPE is a acyclic network

> Any temporal propositional expression can be built as a network (with no cycles).

**Reasoning:** They show four "building block" circuits (Figure 1a-d) that realize:

| Figure | Logic Gate | Circuit Function                             |
|--------|------------|----------------------------------------------|
| **1a** | Delay      | $N_3(t) \equiv N_i(t-1)$                     |
| **1b** | OR         | $N_3(t) \equiv N_1(t−1) \lor N_2(t−1)$       |
| **1c** | AND        | $N_3(t) \equiv N_1(t−1) \land N_2(t−1)$      |
| **1d** | AND-NOT    | $N_3(t) \equiv N_1(t−1) \land \neg N_2(t−1)$ |

Since any logical expression can be built from AND, OR, and NOT (with delays handled by chains of neurons),
ANY TPE can be realized.

They also note there are always **infinitely many topologically different nets realizing the same TPE** – a precursor to the idea
that many different neural architecture can compute the same function.

---

### Theorem 3: Characterization of realizable expression

This theorem gives a necessary and sufficient condition for a complex logical sentence to be a TPE (and hence realizable):

> A sentence is realizable if and only if it evaluate to FALSE when all its constituent predicates are assumed FALSE.

**Intuition:** A neuron can only fire when some input actually fires. If all inputs are silent, the neuron must be silent too.
There is no spontaneous firing from noting. So any realizable expression must be false when all inputs are false. This rules
out things like tautologies (always true) or expression that fires when nothing is happening.

---

### Applied Example: The Heat-Cold Illusion

Through this example they show how a specific psychological phenomenon can be explained by neural logic.

**Phenomenon:** If you touch skin briefly with a cold object, you feel heat. If you hold it longer,
you only feel cold. This is because of different receptors for heat and cold with different "persistence" times.

**Logic:**

Let:

- $N_1$ = heat receptor fires at time $t$.
- $N_2$ = cold receptor fires at time $t$.
- $N_3$ = sensation of heat at time $t$.
- $N_4$ = sensation of cold at time $t$.

They specify:

```math
\begin{aligned}
N_3(t) \;&\equiv\; N_1(t-1) \;\lor\; \big(N_2(t-3) \land \neg N_2(t-2)\big) \\[4pt]
N_4(t) \;&\equiv\; N_2(t-2) \land N_2(t-1)
\end{aligned}
```

Interpretation:

- **Heat sensation** occurs if heat receptor fires, OR if cold receptor fired 3 time-steps ago but NOT
  2 steps ago (i.e., cold started recently but stopped -> feels like heat!).

- **Cold sensation** requires cold receptor firing for 2 consecutive time steps.

---

## Equivalence Theorems

### Theorem 4: Relative and absolute inhibition are equivalent

| Type                | Description                                                            |
|---------------------|------------------------------------------------------------------------|
| Absolute Inhibition | One inhibitory input = neuron CANNOT fire                              |
| Relative Inhibition | One inhibitory input = raises threshold (needs more excitatory inputs) |

They show these are equivalent and can convert one type of network to the other.

---

### Theorem 5: Extinction is equivalent to absolute inhibition

Neurons becoming temporarily refractory after firing can be simulated by adding inhibitory feedback loops.

---

### Theorem 6: Temporal summation is equivalent to spatial summation

A neuron summing inputs over time can be replaced by network where multiple delayed inputs arrive simultaneously
(spatial summation).

---

### Theorem 7: Learning (alterable synapses) is equivalent to circular networks

They show that synapses that strengthen with use (learning) can be simulated by reverberating circuts
(feedback loops).

If a neuron fires and its input synapses are active simultaneously, those synapses become permanently
strengthened. This can be modeled by a circuit that "remembers" previous coincident activity.

---

## Nets With Circles

Network with circles are networks with feedback loops that can sustain activity indefinitely, giving rise
to memory, time-independent behaviour, and computation.

With acknowledgement of circles, it breaks the simple "substitution" method from Theorem 1.
For instance, if you substitute $N_1$ into $N_2$, $N_2$ into $N_3$, and $N_3$ back into $N_1$...,
you could go on forever! The circle means there's no "bottom" to stop at.

The complexity introduced by circles are tackled and they are explained in following steps.

---

### Step 1: Simplifying the Problem

**The Cyclic Set**

Given a network $\mathcal{N}$ with circles:

1. Identify a cyclic set – a minimal set of neurons whose removal would make the network acyclic (no circles left).

2. Let the cyclic set be $c_1, c_2, ..., c_p$ (where $p$ is the order of the network).

3. Every other neuron's firing can be expressed as a TPE in terms of:
    - The cyclic set neurons
    - The peripheral afferents (inputs)

So the **real challenge** is just figuring out the behaviour of those $p$ cyclic neurons.

---

### Step 2: Writing the Cyclic Equations

For each cyclic neuron $N_i$, we can write:

```math
N_i(t)\; \equiv\; Pr_i\;[\;S^{n_{i1}}N_1(t),\; S^{n_{i2}}N_2(t),\; \dots,\; S^{n_{ip}}N_p(t)\;]
```

Where,

- $Pr_i$ is a logical expression involving the cyclic neurons (with various delays $n_{ij}$).
- The delays account for how many synaptic steps it takes to go around the circle.

---

### Step 3: The Mathematical Trick - Aligning Time

**The Common Period $n$**

The authors define $n$ as the **Least Common Multiple** of all the delays $n_{ij}$ in the cyclic equations.

**Why?** Because after $n$ time steps, every cyclic neuron's input are "in phase", i.e., each neuron depends on
the state of the others at the same time offset.

After repeated substitution, the equations become:

```math
N_i(t)\; \equiv\; Pr_i\;[\;S^n N_1(t),\; S^n N_2(t),\; \dots,\; S^n N_p(t)\;]
```

Now all cyclic neurons depend on their **own states from $n$ steps ago**.

---

### Step 4: States and State Transitions

**Defining the State**

At any time $t$, the **state** of the cyclic set is the pattern of which of the $p$ cyclic neurons are firing.
Since each neurons is either ON or OFF, there are $2^p$ possible states. The authors enumerate these states as:

```math
X_1(t),\; X_2(t),\; \dots,\; X_{2^p}(t)
```

Where $X_j(t)$ is true if the network is in state $j$ at time $t$.

**The Transition Function**

Because of the $S^n$ operator, the state at time $t$ depends ONLY on:

- The state at time $t - n$ (one "cycle" ago).
- The peripheral afferents (inputs) during that interval.

So we get a *state transition equation:**

```math
X_i(t)\; \equiv\; \exists{j}\; [\; X_j(t - n) \land P_{ij}(t)\; ]
```

Where $P_{ij}(t)$ is a logical expression saying: "*The inputs during the interval allow a transition from
state $j$ to state $i$*".

---

### Step 5: Unrolling the Loop

1. Start with: $X_i(t)$ depends on $X_i(t - n)$.
2. But $X_i(t - n)$ depends on $X_k(t - 2n)$.
3. And $X_k(t - 2n)$ depends on $X_l(t - 3n)$.
4. ...and so on, all the way back to time 0.

After $s$ steps back in time:

```math
X_i(t)\; \equiv\; \exists{f}\; [\; \text{a sequence of states}\; f(0),\; f(1),\; \dots,\; f(s)\; ]
```

Where $f(k)$ is the state of the network at time $k \cdot n$, and the transitions are constrained by the inputs.

---

### Step 6: The Final Expression

After all the mathematical manipulation, the authors arrive at the following expression (equation 9 in paper):

```math
N_i(t) \; \equiv \; \exists \phi \; \forall x \; (x < t) 
\left[ \;
    \phi(x) \le 2^p \;
    \land \; \phi(t) = i \;
    \land \; P(\phi(x+1), \phi(x)) \;
    \land \; N_{\phi(0)}(0) \;
\right]
```

**Interpretation**

| Symbol                      | Meaning                                                                       |
|-----------------------------|-------------------------------------------------------------------------------|
| $\exists{\phi}$             | There exists a sequence of states $\phi$                                      |
| $\forall x\; (x < t)$       | For all time steps $x$ before $t$                                             |
| $\phi(x)\; \le\; 2^p$       | $\phi(x)$ is valid state (one of the $2^p$ possible patterns)                 |
| $\phi(t)\; =\; i$           | At time $t$, the state is $i$ (the one where neuron $i$ fires)                |
| $P(\phi(x + 1)),\; \phi(x)$ | The transition from state $\phi(x)$ to $\phi(x + 1)$ is allowed by the inputs |
| $N_{\phi(0)}(0)$            | The initial state at time 0 is $\phi(0)                                       |

> Neuron $i$ fires at time $t$ IF AND ONLY IF there exists some sequence of states $\phi$,
> starting from the initial state at time 0, following the allowed transitions, that ends
> with neuron $i$ firing at time $t$.

In other words: **The circle's behaviour is completely determined by its initial state and the sequence of inputs over time**.

---

### Theorem 8 – The Big Result

> Every network with circles has a solution of the form given by Equation 9.

**What this Means**

1. **Predictability:** Given the initial state of cyclic neurons at time 0, and given the sequence of inputs
   over time, we can compute exactly when each cyclic neuron will fire.

2. **Finite Memory:** Even though the circle can reverberate forever, its behaviour depends only on:
    - The initial state (finite information: $2^p$ possibilities).
    - The history of inputs (which is external).

3. **Recursive Functions:** The expression $\exists \phi$ is a **recursive definition** – it references
   itself in a well-founded way.

---

### Theorem 9: The Full Characterization

> The set of classes $a_1, \; a_2, \; \dots, \; a_s$ is realizable by a network with circles IF AND ONLY condition (14) holds.

This is the **complete, necessary and sufficient condition** for whether a given behaviour can be implemented by a neural network
with feedback.

**The Catch**

The condition involves exploring $2^{2^n}$ possible classes – a doubly exponential explosion. This means:

- The theorem is mathematically complete.
- BUT it's computationally intractable for practical use (impossible to check by hand for large networks).

---

### Theorem 10: A Practical Shortcut

> Every member of the set $K$ is realizable.

The set $K$ is defined recursively as:

1. **Any TPE**

2. **Quantified expressions:** $\forall x \; (x < t) \; Pr(x)$ and $\exists x \; (x < t) \; Pr(x)$ – "for all past times"
   and "there exits a past time".

3. **Congruence predicates:** $C_{mn}(t)$ – "$t$ is congruent to $m$ modulo $n$" (i.e., a periodic clock signal).


**How to Build These**

| Expression                      | Network Construction                                                     |
|---------------------------------|--------------------------------------------------------------------------|
| $\forall x \; (x < t) \; Pr(x)$ | "$Pr$ has been true for ALL past times" -> Use an AND gate with feedback |
| $\exists x \; (x < t) \; Pr(x)$ | "$Pr$ has been true at SOME past time" -> Use an OR gate with feedback   |
| $C_{mn}(t)$                     | A simple circular chain of $n$ neurons, tapped at position $m$           |


**Example: Building a "Memory" Circuit**

Suppose you want a neuron that **remembers** whether input $A$ fired at any time in the past:

```math
\text{Memory}(t) \; = \; A(t) \; \lor \; \text{Memory}(t - 1)
```

This is the expression: $\exists x \; (x < t) \; A(x)$

**How to build it:**

1. Take neuron $M$.
2. $M$ receives input from $A$ (excitatory).
3. $M$ also receives input from $M$ itself (excitatory, delayed by 1)
4. Result: Once A fires, M keeps firing forever

This is the **simplest circle**: a self-exciting loop!

---

## The Turing Machine Connection

The paper closes with a single paragraph that turned out to be historically massive:

> It is easily shown: first, that every net, if furnished with a tape, scanners connected to afferents, and suitable efferents to perform the necessary
> motor-operations, can compute only such numbers as can a Turing machine; second, that each of the latter numbers can be computed by such a net; and that nets
> with circles can compute, without scanners and a tape, some of the numbers the machine can, but no others, and not all of them.

In short: **a McCulloch-Pitts net plus an external tape is exactly as powerful as a Turing machine** — no more, no less.

| Type of Network                 | What It Can Compute                                                                                                                        |
|---------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| **Acyclic net**                 | Boolean functions of a fixed, finite window of past inputs. No indefinite memory.                                                            |
| **Net with circles**            | Can remember indefinitely, but with $p$ cyclic neurons it has only $2^p$ states — a finite-state machine, strictly weaker than a Turing machine. |
| **Net with circles + tape**     | Exactly the Turing-computable numbers.                                                                                                       |

From this they draw the philosophical payoff:

> If any number can be computed by an organism, it is computable by these definitions, and conversely.

That is a **psychological justification of the Turing definition** of computability (and of its equivalents, Church's λ-definability and Kleene's primitive
recursiveness): Turing's formalism is claimed to capture what organisms with nervous systems can compute.

{{< fold summary="Why this doesn't mean 'the brain is a Turing machine'" >}}
The equivalence holds only for nets **furnished with a tape**. On their own, nets with circles are finite-state machines, and the authors say so explicitly —
they compute "some of the numbers the machine can, but no others, and not all of them."

So the claim is not neurophysiological ("the brain *is* a Turing machine") but philosophical: neural nets give a plausible biological grounding for Turing's
definition of computability. Even so, this remark was one of the first bridges between the mathematics of computation and the biology of the brain, and it fed
directly into computationalism and into Turing's own 1950 paper "Computing Machinery and Intelligence."
{{< /fold >}}

---

## Consequences

### Causality Is One-Way

> Causality ... never, except in statistics, has it been as irreciprocal as in this theory.

Given the net and the state at time $t$, the state at $t+1$ follows. The reverse fails: disjunction (OR) throws away information, so you cannot recover the
preceding state, nor afferents from central activity, nor central from efferent. And because circles regenerate activity, a firing at time $t$ may trace back to
an input at $t-1$, $t-2$, or any earlier moment — **reference becomes indefinite as to time past**.

> Thus our knowledge of the world, including ourselves, is incomplete as to space and indefinite as to time.

---

### Epistemology: The "Thing in Itself"

Every idea and every sensation is realized by activity within the net, and no such activity fully determines the actual afferents — perception is *constructed*,
never direct access to reality. Alter the net (disease, drugs, injury) and the facts themselves shift: tinnitus, hallucinations, delusions, disorientation.

> With determination of the net, the unknowable object of knowledge, the "thing in itself," ceases to be unknowable.

Kant's noumenon remains out of reach as a *thing*, but the **mapping** from world to percept becomes knowable once the net is specified.

---

### Psychology

> A psychon can be no less than the activity of a single neuron.

The smallest unit of mental activity is one all-or-none firing. Because that activity is inherently propositional, psychons relate to one another by two-valued
logic — so introspective, behavioristic and physiological psychology all rest on the same logical structure.

The paper also drops, in one sentence, what would later become cybernetics: systems that act so as to **reduce the difference** between afferent input and
activity within a regenerative net "exhibit purposive behavior" — homeostasis, appetition, attention.

---

### Psychiatry and the Mind-Body Problem

Irreciprocity has a clinical edge: the same observable behavior may come from organic disease, hysteria, or malingering, and **the net cannot be uniquely
inferred from the behavior**. The same limit shows up in contradictory eyewitness accounts and in memories that fail to match the record.

> The psychiatrist may take comfort ... that, for prognosis, history is never necessary.

The future depends on the net's *current* state and inputs, not on its history — change the net and you change the future. Less comfortingly, the psychiatrist's
observables are explicable only in terms of nervous activity that stays out of direct reach. But at least:

> "Mind" no longer "goes more ghostly than a ghost."

Diseased mentality becomes a pathology of the net, describable in the terms of neurophysiology. No immaterial substance required.

---

### Neurology and Mathematical Biophysics

The theory sharpens the distinction between nets **necessary** and merely **sufficient** for a given activity — damage to a necessary net destroys the function,
whereas another net may compensate for a sufficient one — and so clarifies how disturbed structure relates to disturbed function. For mathematical biophysics it
supplies a formal language (TPEs) for describing known nets, plus a constructive method for building hypothetical nets with required properties.

---

### Final Message

> **Mind is not a ghost in the machine. It is the machine.**

The brain is a logical machine. All mental activity is logical computation. And we can, in principle, understand it completely.
