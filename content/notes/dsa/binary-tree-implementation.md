+++
title = "Binary Tree Implementation"
date = 2026-02-21T20:03:22+05:45
tags = ["TSA", "Binary Tree", "C++"]
series = ["Tree Structures and Algorithms"]
description = "Representation and traversal of binary tree"
math = true
+++


## Binary Tree Types

**Full Binary Tree**: binary tree of height $h$ having maximum number of nodes. adding new node increases the height of tree.

**Complete Binary Tree**: binary tree of height $h$ is full binary tree upto $h - 1$ and in last level elements must be filled
left to right without skipping.


## Array Representation

An array can be filled by storing elements in tree by traversing in [level order](#level-order-traversal).

- **Left Child**: $2i + 1$
- **Right Child**: $2i + 2$
- **Parent Node**: $\lfloor \frac {i - 1} {2} \rfloor$


## Linked Representation

```cpp

template <typename T>
struct BinaryTreeNode
{
    T value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};

using BinaryTree = BinaryTreeNode*;

```


## Tree Traversals

### Pre-Order Traversal

> Visit(node), PreOrder(left subtree), PreOrder(right subtree)


### In-Order Traversal

> InOrder(left subtree), Visit(node), InOrder(right subtree)


### Post-Order Traversal

> PostOrder(left subtree), PostOrder(right subtree), Visit(node)


{{< callout type="tip" title="Can we generate a unique tree from traversals?">}}

Each traversal (preorder, inorder, postorder), if taken alone give catalan numbers of possible trees.
To get a unique tree just from traversal, we need to take inorder + (preorder or postorder).

{{< /callout >}}


### Level-Order Traversal

