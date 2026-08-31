+++
title = "Tokenization"
date = 2026-08-09T11:15:21+05:45
tags = ["nlp"]
math = true
description = "Token meaning and its computation details."
+++


To build NLP models, we need to break text into standard processing units called tokens. Before looking at modern tokenization algorithms,
we must evaluate three natural candidates: words, morphemes, and characters. Each seems reasonable at first glance, but all three fail as
a universal standard.


## The Natural Candidates - Why They Fail?

### Words

**Definition:** The traditional orthographic unit, separated by spaces in some languages.

- **Word Type:** Number of distinct words in a corpus. If vocabulary is $V$, number of types is $|V|$.
- **Word Instance:** Total number of running words, denoted as $N$.

<br/>

**Why words fail as tokens:**  

- **Ambiguous definition:** What counts as a word depends on context and use-case. Do we count punctuation? Fillers (*umm*, *uh*)?
  Fragments (*main*- from *mainly*)? Is They the same type as they?
- **Cross-lingual differences:** Languages like Chinese, Japanese, and Thai don't use spaces to mark word boundaries. Defining orthographic
  words post-hoc in these languages is challenging.
- **Infinite vocabulary growth:** The relationship between $∣V∣$ and $N$ follows **Herdan's Law** (or **Heap's Law**):

$$ |V| = kN^{\beta} $$

where $k$ and $\beta$ are positive constants $(0 < \beta < 1)$.

- Because vocabulary grows endlessly, models will constantly encounter unknown words—a fatal problem for machine learning models.
    - **Function words** (e.g., *a*, *of*) are finite and don't grow indefinitely.
    - **Content words** (nouns, verbs, adjectives) grow without bound.

---

### Morphemes

**Definition:** The minimal meaning-bearing unit in a language. A word can be a single morpheme (*fox*) or a combination of them (*cat*-*s*, *work*-*ed*).

Morphemes are divided into **roots** (the central meaning) and **affixes** (additional meanings). Affixes exist on a continuum:

- **Inflectional:** Grammatical markers (e.g., plural -*s*, past tense -*ed*). They are productive and predictable.
- **Derivational:** Idiosyncratic markers that change grammatical class (e.g., *care* → *careful* → *carefully*).
- **Clitics:** Act syntactically like words but are phonologically attached to another word (e.g., *’ve* in *I’ve*).

<br/>

Languages also vary drastically in **morphological typology:**

- **Isolating languages** (e.g., Vietnamese) have roughly one morpheme per word.
- **Polysynthetic languages** (e.g., Koryak, Inuit) pack entire sentences into a single word.
- **Agglutinative languages** (e.g., Turkish) have clean boundaries between morphemes.
- **Fusional languages** (e.g., Russian) fuse multiple grammatical categories into a single affix, making boundaries blurry.

<br/>

**Why morphemes fail as tokens:**  
Because of morphological typology, morphemes are incredibly hard to define universally. In fusional languages, a single affix might mean "singular,
instrumental, first declension" all at once, making clean segmentation impossible. Furthermore, polysynthetic languages create words so complex that
breaking them into standard morphemes doesn't map well to other languages. It is too difficult to standardize cross-lingually.

---

### Characters

**Definition:** The individual symbols used to write a language, represented in computers via Unicode code points and commonly encoded in UTF-8.

**Why characters fail as tokens:**  
While characters are mathematically well-defined, finite, and solve the unknown-word problem entirely, they are too small a unit.

- They lack inherent semantic meaning (e.g., the letter *c* or *a* means nothing on its own).
- For language like English, tokenizing by character creates unnecessarily long sequences, increasing computational cost.
- In languages like Japanese or Thai, an individual character is simply too granular to capture meaningful linguistic units.
- Models would be forced to learn how to combine characters into meaningful concepts entirely from scratch, wasting representational capacity.

---

## Subword Tokenization

**Subword** is a data-driven token that is smaller than a standard word but carries more semantic weight than a single character. It is typically a meaningful
part of a word, roughly corresponding to a morpheme, and can be further broken down into characters when necessary.

**Tokenization** is the process of segmenting the input text into **tokens**, which serve as the basic units of text representation for a language model.

**Tokenizer** is the algorithm that produces the tokens. To train a LLM, you first need to train a tokenizer.

**Training a tokenizer** is a process of identifying subwords that are of interest and occur most frequently in the corpus at hand.

---

### Byte-Pair Encoding

**Byte-Pair Encoding (BPE)**  was initially developed as an algorithm for compressing text and was later adopted by OpenAI for tokenization when
pre-training GPT models. It is used by several transformer models, including GPT, GPT-2, RoBERTa, BART, and DeBERTa.

BPE has two phases: **training** and **encoding/tokenizing**.

#### BPE Training

The BPE training algorithm iteratively merges frequent neighboring tokens to create longer tokens.

1. **Initialize:** Start with a vocabulary consisting of individual characters. Separate the training corpus into words (usually using whitespace and punctuation).
2. **Count:** Find the most frequent adjacent pair of tokens in the corpus.
3. **Merge:** Combine the pair into a single new token, add it to the vocabulary, and replace all occurrences of the pair in the corpus with the new token.
4. **Repeat:** Continue counting and merging until $k$ merges have been performed. $k$ determines the final vocabulary size.

#### BPE Encoding

Once the vocabulary and the exact sequence of merges have been learned during training, encoding a new test sentence is straightforward:

1. Segment the test sentence into individual characters (respecting the same word boundaries used during training).
2. Apply the $k$ learned merges greedily, in the exact order in which they were learned during training.

Because the encoder strictly applies the learned merges, it can efficiently represent common words seen during training. More importantly, it can break down unknown or
rare words into known subwords (e.g., breaking *lower* into *low* and *er* if *lower* was never seen during training but *low* and *er* were).

#### BPE In Practice

When applied to real-world, large-scale language models, BPE operates with a few key nuances:

- **Byte-level BPE:** Instead of operating directly on Unicode characters, BPE can be applied to the individual **bytes** of UTF-8-encoded text.
  Because there are only 256 possible byte values, the base vocabulary is fixed and small. This guarantees that there are **no unknown tokens**, as any text can be
  represented as a sequence of bytes.
- **Vocabulary Size:** Real models typically perform tens of thousands of merges, resulting in vocabulary sizes ranging from roughly 50,000 to 200,000 tokens.
- **Pre-tokenization:** Before BPE even runs, text is usually split using regular expressions to strip out clitics, punctuation, and spaces.
- **Multilingual Challenges:** Many large language models are trained on English-dominated corpora. Consequently, BPE tokenizers may allocate a large portion of their
  vocabulary to English words. Non-English languages can therefore suffer from **oversegmentation**, where common words are broken into many smaller tokens.
  This increases sequence length, raises computational costs, and can degrade model performance.

---

## Rule-based Tokenization

While data-driven subword tokenization (e.g., BPE) is standard in modern LLMs, some applications require tokens to correspond strictly to **orthographic words**,
such as linguistic research, parsing, and social science. Rule-based tokenization uses predefined, deterministic rules, typically implemented with regular expressions.

### Handling English Nuances

English tokenization requires rules for several ambiguities:

- **Punctuation:** Separate sentence-final punctuation while preserving word-internal punctuation (e.g., `m.p.h.`, `Ph.D.`, `AT&T`).
- **Numbers and Prices:** Keep structured forms intact (e.g., `$45.55`, `01/02/06`, `555,500.50`).
- **Clitics:** Split contractions (e.g., `we're` → `we` `are`, `doesn't` → `does` `n't`).

### The Penn Treebank Standard

The **Penn Treebank** defines a widely used tokenization standard that separates clitics and punctuation while keeping hyphenated words together.

- *Input:* `"The San Francisco-based restaurant," they said, "doesn't charge $10".`
- *Output:* `"` `The` `San` `Francisco-based` `restaurant` `,` `"` `they` `said` `,` `"` `does` `n't` `charge` `$` `10` `"` `.`

### Sentence Segmentation

Sentence segmentation identifies sentence boundaries. While `?` and `!` are usually straightforward, `.` is ambiguous because it can mark either a sentence boundary or
an abbreviation (e.g., `Dr.`, `Inc.`). This is typically handled using abbreviation dictionaries or deterministic rules.

---

## Minimum Edit Distance

To compare how similar two words or strings are (crucial for tasks like spelling correction, machine translation, and speech recognition), we use **edit distance**. 

**Definition:** The minimum number of editing operations (insertions, deletions, substitutions) required to transform one string into another.

### Levenshtein Distance

The most common variant is **Levenshtein distance**, which assigns specific costs to operations:

- **Insertion:** cost 1
- **Deletion:** cost 1
- **Substitution:** cost 2 (equivalent to 1 deletion + 1 insertion), or 0 if substituting a character for itself.

### The Algorithm (Dynamic Programming)

Naively searching all possible edit paths is too slow. Instead, we use **dynamic programming**—a table-driven method that solves the problem by combining solutions
to smaller subproblems.

We build a matrix $D$ where $D[i, j]$ represents the edit distance between the first $i$ characters of the source string and the first $j$ characters of the target string.

**Recurrence Relation:**
$$ D[i, j] = \min \begin{cases} 
D[i-1, j] + 1 & \text{(Deletion)} \\
D[i, j-1] + 1 & \text{(Insertion)} \\
D[i-1, j-1] + \text{sub-cost}(X_i, Y_j) & \text{(Substitution)}
\end{cases} $$
*Where $\text{sub-cost} = 0$ if characters match, and $2$ if they differ.*

**Base Cases:**
- $D[0, 0] = 0$ (Empty string to empty string)
- $D[i, 0] = i$ (Deleting $i$ characters from source to match empty string)
- $D[0, j] = j$ (Inserting $j$ characters into empty string to match target)

### Alignment via Backtrace

Simply knowing the distance number is often not enough; we need to know *how* the strings align. 

By augmenting the algorithm to store **backpointers** in each cell (indicating which neighboring cell we came from), we can perform a **backtrace**.
Starting from the bottom-right corner of the matrix ($D[n, m]$), we follow the pointers back to the origin ($D[0, 0]$). This path reveals the exact sequence of edits
(the alignment) needed to transform the source into the target.


