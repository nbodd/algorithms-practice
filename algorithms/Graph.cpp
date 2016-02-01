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

void bfs(const Graph & graph, int start, vector<int> & parent, vector<int> & distance) {
    vector<bool> visited;
    
    visited.resize(graph.nodeTraverseLimit(), false);
    parent.resize(graph.nodeTraverseLimit(), -1);
    distance.resize(graph.nodeTraverseLimit(), -1);
    
    int time = 0;
    queue<int> foundNodes;
    parent[start] = -1;
    visited[start] = true;
    distance[start] = time;
    
    foundNodes.push(start);
    
    while (!foundNodes.empty()) {
        int node = foundNodes.front();
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


void recurseDfs(const Graph & graph, int node, vector<int> & parent, vector<int> & distance, vector<bool> visited) {
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

void dfs(const Graph & graph, int start, vector<int> & parent, vector<int> & distance) {
    vector<bool> visited;
    
    visited.resize(graph.nodeTraverseLimit(), false);
    parent.resize(graph.nodeTraverseLimit(), -1);
    distance.resize(graph.nodeTraverseLimit(), -1);
    
    parent[start] = -1;
    visited[start] = true;
    distance[start] = 0;
    
    recurseDfs(graph, start, parent, distance, visited);
}

