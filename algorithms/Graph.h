//
//  Graph.h
//  algorithms
//
//  Created by Nick on 1/31/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <vector>

using namespace std;

typedef int Node;

struct Edge {
    Node from;
    Node to;
    int weight;
};


const int MAX_PATH_VALUE = 350000;

class Graph {
public:
    Graph(int numNodes, int numEdges) {
        m_numNodes = numNodes;
        m_numEdges = numEdges;
        
        m_edges.resize(m_numNodes + 1);
        for (int i=0; i<nodeTraverseLimit(); ++i) {
            m_edges[i] = new vector<Edge *>();
        }
    }
    
    ~Graph() {
        for (int i=0; i<nodeTraverseLimit(); ++i) {
            for (auto edgeitr = m_edges[i]->begin(); edgeitr != m_edges[i]->end(); ++edgeitr) {
                delete *edgeitr;
            }
            delete m_edges[i];
        }
    }
    
    int nodeTraverseLimit() const {
        return m_numNodes + 1;
    }
    
    void addEdge(int x, int y, int r) {
        Edge *e = new Edge;
        e->weight = r;
        e->from = x;
        e->to = y;
        
        m_edges[x]->push_back(e);
    }
    
    const vector<Edge *>& getEdges(int node) const {
        return *m_edges[node];
    }
    
private:
    int m_numNodes;
    int m_numEdges;
    vector< vector<Edge *> *> m_edges;
};

void bfs(const Graph & graph, Node start, vector<Node> & parent, vector<int> & distance);

void dfs(const Graph & graph, Node start, vector<Node> & parent, vector<int> & distance);

void dijkstra(const Graph & graph, Node start, vector<Node> & parent, vector<int> & distance);

#endif /* Graph_h */
