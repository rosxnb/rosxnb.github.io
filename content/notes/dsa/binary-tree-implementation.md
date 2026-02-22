+++
title = "Binary Tree Implementation"
date = 2026-02-21T20:03:22+05:45
tags = ["TSA", "Binary Tree", "C++"]
series = ["Tree Structures and Algorithms"]
description = "Representation and traversal of binary tree"
math = true
+++


## Binary Tree Types

### Full Binary Tree

- Contains maximum nodes possible: $n = 2^{h+1} - 1$ for height $h$
- All levels are completely filled; adding any node increases height

---

### Complete Binary Tree

- All levels filled except possibly the last
- Last level nodes filled strictly left to right without gaps
- Every full binary tree is complete, but not vice versa

---

## Array Representation

A binary tree can be stored in an array using **level-order traversal**.

For a node at index $i$:

- **Left Child**  →  $2i + 1$
- **Right Child** →  $2i + 2$
- **Parent**      →  $\left\lfloor \frac{i - 1}{2} \right\rfloor$

These formulas hold only for a **Complete Binary Tree**.

This representation is commonly used in **heaps**.

---

## Linked Representation

Each node explicitly stores pointers to its left and right child.

```cpp
struct BinaryTreeNode
{
    int value;
    std::shared_ptr<BinaryTreeNode> left;
    std::shared_ptr<BinaryTreeNode> right;

    BinaryTreeNode(int value)
        : value(value)
        , left(nullptr)
        , right(nullptr)
    {}
};

using BinaryTree = std::shared_ptr<BinaryTreeNode>;
BinaryTree root = nullptr;
```

---

## Tree Traversals

Traversal = systematic way of visiting all nodes.

{{< callout type="tip" title="Can We Reconstruct a Tree from Traversals?" >}}

A single traversal (preorder, inorder, or postorder) is not sufficient to uniquely determine a binary tree.  
Each alone corresponds to multiple possible trees (Catalan count).

To reconstruct a unique binary tree, we need:

- Inorder + Preorder, or  
- Inorder + Postorder

{{< /callout >}}

---

### Preorder Traversal

Visit node → traverse left subtree → traverse right subtree

```cpp
std::vector<int>
PreOrderTraversal_recursive(BinaryTree root)
{
    std::vector<int> result;
    std::function<void(BinaryTree)> preorder = [&](BinaryTree node) {
        if (!node)
            return;

        result.push_back(node->value);
        preorder(node->left);
        preorder(node->right);
    };

    preorder(root);
    return result;
}
```

---

### Inorder Traversal

Traverse left subtree → visit node → traverse right subtree

```cpp
std::vector<int>
InOrderTraversal_recursive(BinaryTree root)
{
    std::vector<int> result;
    std::function<void(BinaryTree)> inorder = [&](BinaryTree node) {
        if (!node)
            return;

        inorder(node->left);
        result.push_back(node->value);
        inorder(node->right);
    };

    inorder(root);
    return result;
}
```

---

### Postorder Traversal

Traverse left subtree → traverse right subtree → visit node

```cpp
std::vector<int>
PostOrderTraversal_recursive(BinaryTree root)
{
    std::vector<int> result;
    std::function<void(BinaryTree)> postorder = [&](BinaryTree node) {
        if (!node)
            return;

        postorder(node->left);
        postorder(node->right);
        result.push_back(node->value);
    };

    postorder(root);
    return result;
}
```

---

### Level-Order Traversal (BFS)

Traverse nodes level by level from left to right.

```cpp
std::vector<int>
LevelOrderTraversal(BinaryTree root)
{
    if (!root)
        return {};

    std::vector<int> result;
    std::queue<BinaryTree> q;
    q.push(root);

    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        result.push_back(node->value);

        if (node->left)
            q.push(node->left);

        if (node->right)
            q.push(node->right);
    }

    return result;
}
```

{{< callout type="note" title="Implementation File" >}}
Full source: [BinaryTree.cpp](/codefiles/TSA/BinaryTree.cpp)
{{< /callout >}}
