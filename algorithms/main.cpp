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
        
        /*int nodes;
        cin >> nodes;
        
        int edges;
        cin >> edges;
        
        Graph graph(nodes, edges);
        
        for (int edgeNumber = 0; edgeNumber < edges; ++edgeNumber) {
            int x, y, r;
            cin >> x >> y >> r;
            graph.addEdge(x, y, r);
            graph.addEdge(y, x, r);
        }
        
        int start;
        cin >> start;
         */
        
        Graph graph(7, 9);
        graph.addEdge(1, 2, 7);
        graph.addEdge(2, 1, 7);
        graph.addEdge(1, 3, 9);
        graph.addEdge(3, 1, 9);
        
        
        graph.addEdge(1, 6, 14);
        graph.addEdge(6, 1, 14);
        graph.addEdge(2, 3, 10);
        graph.addEdge(3, 2, 10);
        
        
        graph.addEdge(4, 2, 15);
        graph.addEdge(2, 4, 15);
        graph.addEdge(6, 3, 2);
        graph.addEdge(3, 6, 2);
        
        
        graph.addEdge(3, 4, 11);
        graph.addEdge(4, 3, 11);
        graph.addEdge(6, 5, 9);
        graph.addEdge(5, 6, 9);
        
        graph.addEdge(5, 4, 6);
        graph.addEdge(4, 5, 6);
        
        int start = 1;
        
        vector<int> parent;
        vector<int> distance;
        dijkstra(graph, start, parent, distance);
        
        for (int i = 1; i < graph.nodeTraverseLimit(); ++i) {
            if (i != start) {
                cout << ((distance[i] !=  MAX_PATH_VALUE) ? distance[i] : -1 ) << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
