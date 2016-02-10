#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include "Graph.h"

using namespace std;


void missing_numbers() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (int i=0; i<n; ++i) {
        cin >> A[i];
    }
    
    int m;
    cin >> m;
    vector<int> B(m);
    for (int i=0; i<m; ++i) {
        cin >> B[i];
    }
    
    int max = *max_element(B.begin(), B.end());
    
    vector<int> data(max + 1, 0);
    for (int i=0; i<m; ++i) {
        data[B[i]]++;
    }
    
    for (int i=0; i<n; ++i) {
        data[A[i]]--;
    }
    
    for (int i=0; i<(max+1); ++i) {
        if (data[i] != 0) {
            cout << i << " ";
        }
    }
}


/*
void connectedComponentsCutTree(vector<vector<shared_ptr<TreeEdge>>>& edges, vector<int>& cc, vector<bool>& visited,
                                    vector<int>& nodeValues, int start) {
    visited[start] = true;
    cc[cc.size() - 1] += nodeValues[start];
    
    for (auto& vertexEdge : edges[start]) {
        int toVertex = vertexEdge->to;
        if (vertexEdge->disabled == false && visited[vertexEdge->to] == false) {
            connectedComponentsCutTree(edges, cc, visited, nodeValues, toVertex);
        }
    }
}
 */

struct TreeEdge {
    int from;
    int to;
    shared_ptr<TreeEdge> rEdge;
};

int dfsTree(vector<vector<shared_ptr<TreeEdge>>>& edges, vector<bool>& visited, vector<bool>& completed,
                                vector<int>& nodeValues, int start, vector<int>& sum_subtree) {
    visited[start] = true;
    sum_subtree[start] = nodeValues[start];
    
    for (auto& vertexEdge : edges[start]) {
        int toVertex = vertexEdge->to;
        if (visited[vertexEdge->to] == false) {
            sum_subtree[start] += dfsTree(edges, visited, completed, nodeValues, toVertex, sum_subtree);
        } else {
            if (completed[start] == true) {
                sum_subtree[start] += sum_subtree[toVertex];
            }
        }
    }

    completed[start] = true;
    return sum_subtree[start];
}

void cut_the_tree() {
    int n;
    cin >> n;
    vector<int> nodeValues(n);
    for (int i=0; i<n; ++i) {
        cin >> nodeValues[i];
    }
    
    vector<vector<shared_ptr<TreeEdge>>> edges(n);
    for (int i=0; i < (n-1); ++i) {
        int x, y;
        cin >> x >> y;
        
        auto e1 = make_shared<TreeEdge>();
        e1->from = x - 1;
        e1->to = y-1;
        
        auto e2 = make_shared<TreeEdge>();
        e2->from = y-1;
        e2->to = x-1;
        
        e1->rEdge = e2;
        e2->rEdge = e1;
        
        edges[x-1].push_back(e1);
        edges[y-1].push_back(e2);
    }
    
    
    // Do DFS to store the sum of node values under the tree for each node
    vector<int> sum_subtree(n, 0);
    vector<bool> visited(n, false);
    vector<bool> completed(n, false);
    for (int vertex = 0; vertex < n; ++vertex) {
        for (auto& vertexEdge : edges[vertex]) {
            if (false == visited[vertex]) {
                dfsTree(edges, visited, completed, nodeValues, vertex, sum_subtree);
            }
        }
    }
        
    int totalSumOfNodes = *max_element(sum_subtree.begin(), sum_subtree.end());
    
    vector<int> tree_diff;
    for (int vertex = 0; vertex < n; ++vertex) {
        for (auto& vertexEdge : edges[vertex]) {
            int toVertex = vertexEdge->to;
            
            int x = sum_subtree[vertex];
            int y = sum_subtree[toVertex];
            
            int firstTree = (x > y) ? x : y;
            int secondTree = (x > y) ? y : x;
            
            int firstTreeVal;
            if (firstTree == totalSumOfNodes) {
                firstTreeVal = firstTree - secondTree;
            } else {
                firstTreeVal = totalSumOfNodes - secondTree;
            }
            
            int secondTreeVal = secondTree;
            
            int tree_diff_val = abs(firstTreeVal - secondTreeVal);
            tree_diff.push_back(tree_diff_val);
        }
    }

    
    cout << *min_element(tree_diff.begin(), tree_diff.end()) << endl;
}

int searching_main() {
    return 0;
}