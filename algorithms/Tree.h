//
//  Tree.h
//  algorithms
//
//  Created by Nick on 2/1/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include "Graph.h"
#include <vector>

using namespace std;

class GraphTree {
public:
    GraphTree(int nodes) :
        m_tree(nodes, GraphType::DIRECTED_UNIQUE_EDGE)
    {
        
    }
    
    void addEdge(int x, int y, int edgeWeight = 1) {
        m_tree.addEdge(x, y, edgeWeight);
    }
    
    void subtree(vector<Node>& parent, vector<int> & forestSizes) const;
    
    inline int getNumNodes() {
        return m_tree.getNumNodes();
    }
    
    inline int nodeTraverseLimit() const {
        return m_tree.nodeTraverseLimit();
    }
    
private:
    
    void subtreeSize(Node node, vector<int> & forestSizes) const;
    
    Graph m_tree;
};

int evenTree(const GraphTree & tree);

#endif /* Tree_h */
