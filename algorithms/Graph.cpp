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