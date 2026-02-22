#include <vector>
#include <memory>
#include <queue>
#include <stack>
#include <functional>
#include <cassert>
#include <iostream>

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

BinaryTree ConstructBinaryTree()
{
    // Constructing a sample binary tree:
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6

    auto root = std::make_shared<BinaryTreeNode>(1);
    root->left = std::make_shared<BinaryTreeNode>(2);
    root->right = std::make_shared<BinaryTreeNode>(3);
    root->left->left = std::make_shared<BinaryTreeNode>(4);
    root->left->right = std::make_shared<BinaryTreeNode>(5);
    root->right->right = std::make_shared<BinaryTreeNode>(6);
    
    return root;
}

std::vector<int>
LevelOrderTraversal(BinaryTree root)
{
    if (!root)
        return {};

    std::vector<int> result;
    std::queue<BinaryTree> q;

    q.push(root);
    result.push_back(root->value);

    while (!q.empty()) {
        auto node = q.front();
        q.pop();

        if (node->left) {
            result.push_back(node->left->value);
            q.push(node->left);
        }

        if (node->right) {
            result.push_back(node->right->value);
            q.push(node->right);
        }
    }

    return result;
}

std::vector<int>
GenerateArrayRepresentation(BinaryTree root)
{
    return LevelOrderTraversal(root);
}

BinaryTree
GenerateLinkedRepresentation(std::vector<int> levelOrder)
{
    if (levelOrder.empty())
        return {};
    
    auto root = std::make_shared<BinaryTreeNode>(levelOrder[0]);
    std::queue<BinaryTree> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < levelOrder.size()) {
        BinaryTree current = q.front();
        q.pop();
        
        if (i < levelOrder.size()) {
            current->left = std::make_shared<BinaryTreeNode>(levelOrder[i++]);
            q.push(current->left);
        }
        
        if (i < levelOrder.size()) {
            current->right = std::make_shared<BinaryTreeNode>(levelOrder[i++]);
            q.push(current->right);
        }
    }
    
    return root;
}

std::vector<int>
PreOrderTraversal_recursive(BinaryTree root)
{
    std::vector<int> result;
    std::function<void(BinaryTree)> preorder = [&](BinaryTree root) {
        if (!root)
            return;

        result.push_back(root->value);
        preorder(root->left);
        preorder(root->right);
    };

    preorder(root);
    return result;
}

std::vector<int>
PreOrderTraversal_iterative(BinaryTree root)
{
    if (!root)
        return {};

    std::vector<int> result;
    std::stack<BinaryTree> s;

    s.push(root);

    while (!s.empty()) {
        auto node = s.top();
        s.pop();
        result.push_back(node->value);

        if (node->right)
            s.push(node->right);
        if (node->left)
            s.push(node->left);
    }

    return result;
}

std::vector<int>
InOrderTraversal_recursive(BinaryTree root)
{
    std::vector<int> result;
    std::function<void(BinaryTree)> inorder = [&](BinaryTree root) {
        if (!root)
            return;

        inorder(root->left);
        result.push_back(root->value);
        inorder(root->right);
    };

    inorder(root);
    return result;
}

std::vector<int>
InOrderTraversal_iterative(BinaryTree root)
{
    if (!root)
        return {};

    std::vector<int> result;
    std::stack<BinaryTree> s;

    auto node = root;
    while (node || !s.empty()) {
        // exhaust leftmost branch for current node
        while (node) {
            s.push(node);
            node = node->left;
        }

        node = s.top();
        s.pop();

        result.push_back(node->value);

        node = node->right;
    }

    return result;
}

std::vector<int>
PostOrderTraversal_recursive(BinaryTree root)
{
    std::vector<int> result;
    std::function<void(BinaryTree)> postorder = [&](BinaryTree root) {
        if (!root)
            return;

        postorder(root->left);
        postorder(root->right);
        result.push_back(root->value);
    };

    postorder(root);
    return result;
}

std::vector<int>
PostOrderTraversal_iterative(BinaryTree root)
{
    if (!root)
        return {};

    std::vector<int> result;
    std::stack<BinaryTree> s1, s2;

    s1.push(root);
    
    while (!s1.empty()) {
        BinaryTree current = s1.top();
        s1.pop();
        s2.push(current);
        
        if (current->left)
            s1.push(current->left);
        if (current->right)
            s1.push(current->right);
    }
    
    while (!s2.empty()) {
        result.push_back(s2.top()->value);
        s2.pop();
    }
    
    return result;
}

void PrintVector(const std::vector<int>& vec)
{
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

void RunTests()
{
    std::cout << "Running Binary Tree Traversal Tests\n";
    std::cout << "====================================\n\n";
    
    // Test 1: Construct binary tree
    BinaryTree tree = ConstructBinaryTree();
    std::cout << "Test 1: Tree Construction\n";
    std::cout << "Expected tree structure:\n";
    std::cout << "        1\n";
    std::cout << "       / \\\n";
    std::cout << "      2   3\n";
    std::cout << "     / \\   \\\n";
    std::cout << "    4   5   6\n\n";
    
    // Test 2: Level Order Traversal
    std::vector<int> levelOrder = LevelOrderTraversal(tree);
    std::vector<int> expectedLevelOrder = {1, 2, 3, 4, 5, 6};
    std::cout << "Test 2: Level Order Traversal\n";
    std::cout << "Expected: "; PrintVector(expectedLevelOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(levelOrder); std::cout << "\n";
    assert(levelOrder == expectedLevelOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 3: Pre-order Traversal (Recursive)
    std::vector<int> preOrderRec = PreOrderTraversal_recursive(tree);
    std::vector<int> expectedPreOrder = {1, 2, 4, 5, 3, 6};
    std::cout << "Test 3: Pre-order Traversal (Recursive)\n";
    std::cout << "Expected: "; PrintVector(expectedPreOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(preOrderRec); std::cout << "\n";
    assert(preOrderRec == expectedPreOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 4: Pre-order Traversal (Iterative)
    std::vector<int> preOrderIter = PreOrderTraversal_iterative(tree);
    std::cout << "Test 4: Pre-order Traversal (Iterative)\n";
    std::cout << "Expected: "; PrintVector(expectedPreOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(preOrderIter); std::cout << "\n";
    assert(preOrderIter == expectedPreOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 5: In-order Traversal (Recursive)
    std::vector<int> inOrderRec = InOrderTraversal_recursive(tree);
    std::vector<int> expectedInOrder = {4, 2, 5, 1, 3, 6};
    std::cout << "Test 5: In-order Traversal (Recursive)\n";
    std::cout << "Expected: "; PrintVector(expectedInOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(inOrderRec); std::cout << "\n";
    assert(inOrderRec == expectedInOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 6: In-order Traversal (Iterative)
    std::vector<int> inOrderIter = InOrderTraversal_iterative(tree);
    std::cout << "Test 6: In-order Traversal (Iterative)\n";
    std::cout << "Expected: "; PrintVector(expectedInOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(inOrderIter); std::cout << "\n";
    assert(inOrderIter == expectedInOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 7: Post-order Traversal (Recursive)
    std::vector<int> postOrderRec = PostOrderTraversal_recursive(tree);
    std::vector<int> expectedPostOrder = {4, 5, 2, 6, 3, 1};
    std::cout << "Test 7: Post-order Traversal (Recursive)\n";
    std::cout << "Expected: "; PrintVector(expectedPostOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(postOrderRec); std::cout << "\n";
    assert(postOrderRec == expectedPostOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 8: Post-order Traversal (Iterative)
    std::vector<int> postOrderIter = PostOrderTraversal_iterative(tree);
    std::cout << "Test 8: Post-order Traversal (Iterative)\n";
    std::cout << "Expected: "; PrintVector(expectedPostOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(postOrderIter); std::cout << "\n";
    assert(postOrderIter == expectedPostOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 9: GenerateArrayRepresentation
    std::vector<int> arrayRep = GenerateArrayRepresentation(tree);
    std::cout << "Test 9: GenerateArrayRepresentation\n";
    std::cout << "Expected: "; PrintVector(expectedLevelOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(arrayRep); std::cout << "\n";
    assert(arrayRep == expectedLevelOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 10: GenerateLinkedRepresentation
    BinaryTree reconstructedTree = GenerateLinkedRepresentation(expectedLevelOrder);
    std::vector<int> reconstructedLevelOrder = LevelOrderTraversal(reconstructedTree);
    std::cout << "Test 10: GenerateLinkedRepresentation\n";
    std::cout << "Expected: "; PrintVector(expectedLevelOrder); std::cout << "\n";
    std::cout << "Actual  : "; PrintVector(reconstructedLevelOrder); std::cout << "\n";
    assert(reconstructedLevelOrder == expectedLevelOrder);
    std::cout << "✓ Passed\n\n";
    
    // Test 11: Edge case - empty tree
    BinaryTree emptyTree = nullptr;
    std::cout << "Test 11: Edge Cases - Empty Tree\n";
    assert(LevelOrderTraversal(emptyTree).empty());
    assert(PreOrderTraversal_recursive(emptyTree).empty());
    assert(PreOrderTraversal_iterative(emptyTree).empty());
    assert(InOrderTraversal_recursive(emptyTree).empty());
    assert(InOrderTraversal_iterative(emptyTree).empty());
    assert(PostOrderTraversal_recursive(emptyTree).empty());
    assert(PostOrderTraversal_iterative(emptyTree).empty());
    std::cout << "✓ All empty tree tests passed\n\n";
    
    // Test 12: Single node tree
    auto singleNode = std::make_shared<BinaryTreeNode>(42);
    std::cout << "Test 12: Edge Cases - Single Node Tree\n";
    std::vector<int> singleNodeExpected = {42};
    assert(LevelOrderTraversal(singleNode) == singleNodeExpected);
    assert(PreOrderTraversal_recursive(singleNode) == singleNodeExpected);
    assert(PreOrderTraversal_iterative(singleNode) == singleNodeExpected);
    assert(InOrderTraversal_recursive(singleNode) == singleNodeExpected);
    assert(InOrderTraversal_iterative(singleNode) == singleNodeExpected);
    assert(PostOrderTraversal_recursive(singleNode) == singleNodeExpected);
    assert(PostOrderTraversal_iterative(singleNode) == singleNodeExpected);
    std::cout << "✓ All single node tests passed\n\n";
    
    std::cout << "====================================\n";
    std::cout << "All tests passed successfully! 🎉\n";
}

int main()
{
    RunTests();
    return 0;
}
