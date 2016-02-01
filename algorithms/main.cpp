//
//  main.cpp
//  algorithms
//
//  Created by Nick on 1/31/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include <iostream>
#include "Graph.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    int testCases;
    cin >> testCases;
    for (int test = 0; test < testCases; ++test) {
        int nodes;
        cin >> nodes;
        
        int edges;
        cin >> edges;
        
        Graph graph(nodes, edges);
        
        for (int edgeNumber = 0; edgeNumber < edges; ++edgeNumber) {
            int x, y;
            cin >> x >> y;
            graph.addEdge(x, y, 1);
            graph.addEdge(y, x, 1);
        }
        
        int start;
        cin >> start;
        
        vector<int> parent;
        vector<int> distance;
        bfs(graph, start, parent, distance);
        
        for (int i = 1; i < nodes + 1; ++i) {
            if (i != start) {
                cout << ((distance[i] != -1) ? distance[i] * 6 : -1) << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
