//
//  Graph.cpp
//  algorithms
//
//  Created by Nick on 1/31/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include "Graph.h"

using namespace std;

void bfs(const Graph & graph, Node start, vector<Node> & parent, vector<int> & distance) {
    vector<bool> visited;
    
    visited.resize(graph.nodeTraverseLimit(), false);
    parent.resize(graph.nodeTraverseLimit(), -1);
    distance.resize(graph.nodeTraverseLimit(), -1);
    
    queue<Node> foundNodes;
    parent[start] = -1;
    visited[start] = true;
    distance[start] = 0;
    
    foundNodes.push(start);
    
    while (!foundNodes.empty()) {
        Node node = foundNodes.front();
        foundNodes.pop();
        
        const vector<Edge *> & nodeEdges = graph.getEdges(node);
        for (auto edge : nodeEdges) {
            int neighbor = edge->to;
            if (false == visited[neighbor]) {
                foundNodes.push(neighbor);
                
                visited[neighbor] = true;
                parent[neighbor] = edge->from;
                distance[neighbor] = distance[edge->from] + 1;
            }
        }
    }
}


void recurseDfs(const Graph & graph, Node node, vector<Node> & parent,
                        vector<int> & distance, vector<bool> visited) {
    const vector<Edge *> & nodeEdges = graph.getEdges(node);
    for (auto edge : nodeEdges) {
        int neighbor = edge->to;
        if (false == visited[neighbor]) {
            parent[neighbor] = node;
            visited[neighbor] = true;
            distance[neighbor] = distance[node] + 1;
            recurseDfs(graph, neighbor, parent, distance, visited);
        }
    }
}

void dfs(const Graph & graph, Node start, vector<Node> & parent, vector<int> & distance) {
    vector<bool> visited;
    
    visited.resize(graph.nodeTraverseLimit(), false);
    parent.resize(graph.nodeTraverseLimit(), -1);
    distance.resize(graph.nodeTraverseLimit(), -1);
    
    parent[start] = -1;
    visited[start] = true;
    distance[start] = 0;
    
    recurseDfs(graph, start, parent, distance, visited);
}

void dijkstra(const Graph & graph, int start, vector<int> & parent, vector<int> & distance) {
    vector<bool> visited;
    
    visited.resize(graph.nodeTraverseLimit(), false);
    parent.resize(graph.nodeTraverseLimit(), -1);
    distance.resize(graph.nodeTraverseLimit(), MAX_PATH_VALUE);
    
    priority_queue< pair<int, Node>, vector< pair<int, Node> >, EdgeCompare >foundNodes;
    
    parent[start] = -1;
    distance[start] = 0;
    
    foundNodes.push(pair<int, Node>(0, start));
    
    while (false == foundNodes.empty()) {
        Node node = foundNodes.top().second;
        foundNodes.pop();
        
        if (false == visited[node]) {
            visited[node] = true;
            
            const vector<Edge *> & edges = graph.getEdges(node);
            for (auto edge : edges) {
                Node neighbor = edge->to;
                bool neighborNotVisited = (visited[neighbor] == false);
                
                int altDistance = distance[node] + edge->weight;
                if ( neighborNotVisited && (altDistance < distance[neighbor]) ) {
                    foundNodes.push(pair<int, Node>(altDistance, neighbor));
                    distance[neighbor] = altDistance;
                    parent[neighbor] = node;
                }
            }
        }
    }
}

void floydWarshall(const Graph & graph, vector<vector<int>> & distance) {
    distance.resize(graph.nodeTraverseLimit());
    for (auto i=1; i<graph.nodeTraverseLimit(); ++i) {
        distance[i].resize(graph.nodeTraverseLimit(), MAX_PATH_VALUE);
    }
    
    for (auto i=1; i<graph.nodeTraverseLimit(); ++i) {
        distance[i][i] = 0;
    }
    
    for (auto i=1; i<graph.nodeTraverseLimit(); ++i) {
        const auto& nodeEdges = graph.getEdges(i);
        for (auto edge : nodeEdges) {
            distance[edge->from][edge->to] = edge->weight;
        }
    }
    
    for (auto k=1; k<graph.nodeTraverseLimit(); ++k) {
        for (auto i=1; i<graph.nodeTraverseLimit(); ++i) {
            for (auto j=1; j<graph.nodeTraverseLimit(); ++j) {
                if (distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

#include <set>

int crab_graphs(const Graph& graph, int feet) {
    set<Node> remainingNodes;
    priority_queue<pair<int, Node>, vector<pair<int, Node>>, EdgeCompare> numEdgesofNodes;
    
    for (int i=1; i<graph.nodeTraverseLimit(); ++i) {
        remainingNodes.insert(i);
        numEdgesofNodes.push(pair<int, Node>(graph.getEdges(i).size(), i));
    }
    
    int crabs = 0;
    int crabVertices = 0;
    while (false == remainingNodes.empty() && false == numEdgesofNodes.empty()) {
        int numEdges = numEdgesofNodes.top().first;
        const auto& currentNode = numEdgesofNodes.top().second;
        numEdgesofNodes.pop();
        
        if (numEdges >= feet) {
            auto currentNodeEdges = graph.getEdges(currentNode);
            int nodeCounter = 0;
            
            for (auto edge : currentNodeEdges) {
                Node toNode = edge->to;
                
                auto remainingNodesItr = remainingNodes.find(toNode);
                if (remainingNodesItr != remainingNodes.end()) {
                    nodeCounter++;
                    remainingNodes.erase(remainingNodesItr);
                    
                    if (nodeCounter == feet) {
                        crabs++;
                        
                        // remove the currentNode from remaining nodes
                        remainingNodes.erase(currentNode);
                        crabVertices += (feet + 1); //1 for currentNode
                        
                        break;
                    }
                }
                
            }
            
        }
        
    }
    
    
    return crabVertices;
}

void connectedComponent(const vector<vector<int>> &pairs, int start, vector<int>& ccData, vector<bool>& visited) {
    visited[start] = true;
    ccData[ccData.size() - 1]++;
    for (auto nextVertex : pairs[start]) {
        if (visited[nextVertex] == false) {
            connectedComponent(pairs, nextVertex, ccData, visited);
        }
    }
}

int journey_to_moon()
{
    int N, I;
    cin >> N >> I;
    vector<vector<int> > pairs(N);
    for (int i = 0; i < I; ++i) {
        int a, b;
        cin >> a >> b;
        pairs[a].push_back(b);
        pairs[b].push_back(a);
    }
    
    long long result = 0;
    vector<int> numAstronautsCC(N);
    vector<bool> visited(N, false);
    for (int i=0; i<N; ++i) {
        if (visited[i] == false) {
            numAstronautsCC.push_back(0);
            connectedComponent(pairs, i, numAstronautsCC, visited);
        }
    }
    
    for (auto val : numAstronautsCC) {
        result += (N - val) * val;
    }
    
   
    cout << result / 2 << endl;
    return 0;
}

void connectedComponentsGrid(vector<vector<int>> & data, int row, int col, vector<vector<bool>> & visited, vector<int> & cc) {
    visited[row][col] = true;
    cc[cc.size() - 1]++;
    // check 8 blocks around the box
    for (int i = row - 1; i <= (row + 1); ++i) {
        for (int j = col - 1; j <= (col + 1); ++j) {
            bool rowLimits = (i >= 0 && i < data.size());
            bool colLimits = (j >= 0 && j < data[col].size());
            if ( rowLimits && colLimits) {
                if (false == visited[i][j] && data[i][j]) {
                    connectedComponentsGrid(data, i, j, visited, cc);
                }
            }
        }
    }
}

void connected_grid() {
    int m, n;
    cin >> m >> n;
    
    vector<vector<int>> data(m);
    vector<vector<bool>> visited(m);
    for (int row=0; row<m; ++row) {
        data[row].resize(n);
        visited[row].resize(n);
        for (int col = 0; col < n ; ++col) {
            cin >> data[row][col];
            visited[row][col] = false;
        }
    }
    
    vector<int> cc;
    for (int row=0; row < m; ++row) {
        for (int col=0; col < n; ++col) {
            if (data[row][col]) {
                cc.push_back(0);
                connectedComponentsGrid(data, row, col, visited, cc);
            }
        }
    }
    
    cout << *max_element(cc.begin(), cc.end()) << endl;
    
}

int main() {
    connected_grid();
    return 0;
}
