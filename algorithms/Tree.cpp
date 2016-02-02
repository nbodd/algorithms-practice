//
//  Tree.cpp
//  algorithms
//
//  Created by Nick on 2/1/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include "Tree.h"
#include <queue>

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