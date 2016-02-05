//
//  greedy.cpp
//  algorithms
//
//  Created by Nick on 2/5/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include <vector>
#include <iostream>

using namespace std;

bool lexographic_grid(vector<vector<char>> & grid) {
    for (auto& row : grid) {
        std::sort(row.begin(), row.end());
    }
    
    // check cols
    for (int col=0; col<grid.size(); ++col) {
        for (int row=1; row<grid.size(); ++row) {
            if (grid[row][col] < grid[row-1][col]) {
                return false;
            }
        }
    }
    
    return true;
}

int main() {
    int testCases;
    cin >> testCases;
    for (int i=0; i<testCases; ++i) {
        int n;
        cin >> n;
        vector<vector<char>> grid;
        for (int j=0; j<n; ++j) {
            string text;
            cin >> text;
            vector<char> row;
            row.insert(row.begin(), text.begin(), text.end());
            grid.push_back(row);
        }
        cout << (lexographic_grid(grid) ? "YES" : "NO") << endl;
    }
    return 0;
}