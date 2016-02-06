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

enum class GraphType {
    UNIQUE_EDGE,
    MULTIPLE_EDGE,
    DIRECTED_UNIQUE_EDGE,
    DIRECTED_MULTIPLE_EDGE
};

const int MAX_PATH_VALUE = 350000;

class Graph {
public:
    Graph(int numNodes, GraphType graphType = GraphType::MULTIPLE_EDGE) {
        m_numNodes = numNodes;
        m_numEdges = 0;
        m_graphType = graphType;
        
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
        if (m_graphType == GraphType::UNIQUE_EDGE || m_graphType == GraphType::DIRECTED_UNIQUE_EDGE) {
            bool edgeFound = false;
            const auto& xEdges = getEdges(x);
            for (auto edge : xEdges) {
                // assume the latest one overwrites the earlier one
                if (edge->to == y) {
                    edge->weight = r;
                    edgeFound = true;
                }
            }
            
            if (m_graphType == GraphType::UNIQUE_EDGE) {
                const auto& yEdges = getEdges(y);
                for (auto edge : yEdges) {
                    // assume latest edges overwrites the earlier one
                    if (edge->to == x) {
                        edge->weight = r;
                        edgeFound = true;
                    }
                }
            }
            
            if (edgeFound) {
                return;
            }
        }
        
        Edge *eX = new Edge;
        eX->weight = r;
        eX->from = x;
        eX->to = y;
        
        m_edges[x]->push_back(eX);
        m_numEdges++;
        
        if (m_graphType == GraphType::MULTIPLE_EDGE || m_graphType == GraphType::UNIQUE_EDGE ) {
            Edge *eY = new Edge;
            eY->weight = r;
            eY->from = y;
            eY->to = x;
            
            m_edges[y]->push_back(eY);
            m_numEdges++;
        }
    }
    
    const vector<Edge *>& getEdges(int node) const {
        return *m_edges[node];
    }
    
    inline int getNumNodes() const {
        return m_numNodes;
    }
    
    inline int getNumEdges() const {
        return m_numEdges;
    }
    
private:
    int m_numNodes;
    int m_numEdges;
    GraphType m_graphType;
    vector< vector<Edge *> *> m_edges;
};

class EdgeCompare {
public:
    bool operator()(pair<int, Node> & a, pair<int, Node> & b) {
        return a.first > b.first;
    }
};

void bfs(const Graph & graph, Node start, vector<Node> & parent, vector<int> & distance);

void dfs(const Graph & graph, Node start, vector<Node> & parent, vector<int> & distance);

void dijkstra(const Graph & graph, Node start, vector<Node> & parent, vector<int> & distance);

void floydWarshall(const Graph & graph, vector<vector<int>> & distance);

int crab_graphs(const Graph& graph, int feet);

#endif /* Graph_h */
