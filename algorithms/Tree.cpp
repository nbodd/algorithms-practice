//
//  Tree.cpp
//  algorithms
//
//  Created by Nick on 2/1/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include "Tree.h"
#include <queue>
#include <iostream>

void GraphTree::subtreeSize(Node node, vector<int> & forestSizes) const {
    const auto& currentNodeEdges = m_tree.getEdges(node);
    
    if (currentNodeEdges.empty()) {
        return;
    }
    
    for (auto edge: currentNodeEdges) {
        subtreeSize(edge->to, forestSizes);
        forestSizes[node] += forestSizes[edge->to];
    }
}

void GraphTree::subtree(vector<Node>& parent, vector<int> & forestSizes) const {
    forestSizes.resize(nodeTraverseLimit(), 1);
    parent.resize(nodeTraverseLimit(), -1);
    
    for (auto i=0; i<nodeTraverseLimit(); ++i) {
        // each node has only one edge pointing to the parent
        const auto& currentNodeEdges = m_tree.getEdges(i);
        
        for (auto edge: currentNodeEdges) {
            parent[edge->to] = edge->from;
        }
    }
    
    if (m_tree.getNumNodes()) {
        subtreeSize(1, forestSizes);
    }
}

int evenTree(const GraphTree & tree) {
    // first find the number of nodes in each subtree
    vector<int> forestSizes;
    vector<Node> parent;
    tree.subtree(parent, forestSizes);
    
    priority_queue<pair<int, Node>, vector<pair<int, Node>>, EdgeCompare> subtrees;
    for (auto i = 1; i < tree.nodeTraverseLimit(); ++i) {
        subtrees.push(pair<int, Node>(forestSizes[i], i));
    }
    
    // start removing the smallest even subtree
    // remove next smallest even subtree -- until all even-subtree-nodes are complete trees
    int edgesRemoved = 0;
    while(false == subtrees.empty()) {
        auto subtreeSize = subtrees.top().first;
        auto currentNode = subtrees.top().second;
        subtrees.pop();
        
        if ((subtreeSize % 2) == 0) {
            if (parent[currentNode] != -1) {
                parent[currentNode] = -1;
                edgesRemoved += 1;
            }
        } else {
            // do nothing
        }
    }
    
    return edgesRemoved;
}

struct TreeNode {
    int value;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
};

void printTree(shared_ptr<TreeNode> tree) {
    if (tree != nullptr) {
        cout << tree->value << " ";
        printTree(tree->left);
        printTree(tree->right);
    }
}

shared_ptr<TreeNode> recurse_inorder_postorder(vector<int>& inorder,
                            vector<int>& postorder, int inStart, int inEnd,
                                        int postStart, int postEnd) {
    
    if (inStart > inEnd) {
        return nullptr;
    } else if (inStart == inEnd) {
        shared_ptr<TreeNode> currentNode = make_shared<TreeNode>();
        currentNode->value = inorder[inStart];
        currentNode->left = nullptr;
        currentNode->right = nullptr;
        return currentNode;
    } else {
        shared_ptr<TreeNode> currentNode = make_shared<TreeNode>();
        int nodeValue = postorder[postEnd];
        currentNode->value = nodeValue;
        
        //find nodeValue in inorder
        int inorder_index = -1;
        for (int i=inStart; i<=inEnd; ++i) {
            if (inorder[i] == nodeValue) {
                inorder_index = i;
                break;
            }
        }
        
        int length = inorder_index - inStart;
        
        currentNode->left = recurse_inorder_postorder(inorder , postorder,
                                                      inStart, inorder_index - 1,
                                                       postStart, postStart + length - 1);
        currentNode->right = recurse_inorder_postorder(inorder, postorder,
                                                       inorder_index + 1, inEnd,
                                                       postStart + length, postEnd - 1);
        
        return currentNode;
    }
}

void construct_tree_from_inorder_postorder() {
    int n = 8;
    //cin >> n;
    
    vector<int> inorder = { 4, 2, 5, 1, 6, 7, 3, 8};
    /*
    for (int i=0; i<n; ++i) {
        cin >> inorder[i];
    } */
    
    vector<int> postorder = {4, 5, 2, 6, 7, 8, 3, 1};
    /*
    for (int i=0; i<n; ++i) {
        cin >> postorder[i];
    }*/
    
    shared_ptr<TreeNode> tree = recurse_inorder_postorder(inorder, postorder, 0, n-1, 0, n-1);
    
    printTree(tree);
}

shared_ptr<TreeNode> recurse_inorder_preorder(vector<int>& inorder, vector<int> &preorder,
                                              int inStart, int inEnd, int preStart, int preEnd) {
    
    if (inStart > inEnd) {
        return nullptr;
    } else if (inStart == inEnd) {
        shared_ptr<TreeNode> current = make_shared<TreeNode>();
        current->value = inorder[inStart];
        current->left = nullptr;
        current->right = nullptr;
        return current;
    } else {
        shared_ptr<TreeNode> current = make_shared<TreeNode>();
        int nodeValue = preorder[preStart];
        current->value = nodeValue;
        
        int inorder_index = -1;
        for (int i=inStart; i<=inEnd; ++i) {
            if (inorder[i] == nodeValue) {
                inorder_index = i;
                break;
            }
        }
        
        int length = (inorder_index - inStart);
        
        current->left = recurse_inorder_preorder(inorder, preorder, inStart, inorder_index - 1, preStart + 1, preStart + length);
        current->right = recurse_inorder_preorder(inorder, preorder, inorder_index + 1, inEnd, preStart + length + 1, preEnd);
        return current;
    }
}

void construct_tree_from_inorder_preorder() {
    int n = 8;
    //cin >> n;
    
    vector<int> inorder = { 4, 2, 5, 1, 6, 7, 3, 8};
    /*
     for (int i=0; i<n; ++i) {
     cin >> inorder[i];
     } */
    
    vector<int> preorder = {1, 2, 4, 5, 3, 7, 6, 8};
    /*
     for (int i=0; i<n; ++i) {
     cin >> postorder[i];
     }*/
    
    shared_ptr<TreeNode> tree = recurse_inorder_preorder(inorder, preorder, 0, n-1, 0, n-1);
    
    printTree(tree);
}

int tree_main() {
    //construct_tree_from_inorder_postorder();
    construct_tree_from_inorder_preorder();
    return 0;
}