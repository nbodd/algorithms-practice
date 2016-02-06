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

/*
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
*/

bool burger_orders_sort(pair<int, int> & a, pair<int, int>& b) {
    if (a.second == b.second) {
        return a.first < a.second;
    }
    return (a.second < b.second);
}

void burger_orders(vector<pair<int, int>> &orders, vector<int> & delivery) {
    std::sort(orders.begin(), orders.end(), burger_orders_sort);
    for (auto& order : orders) {
        delivery.push_back(order.first);
    }
}

int burgers_main() {
    int burgers;
    cin >> burgers;
    vector<pair<int, int>> orders;
    for (int i=0; i<burgers; ++i) {
        int time; int duration;
        cin >> time >> duration;
        orders.push_back(pair<int, int>(i + 1, time + duration));
    }
    vector<int> delivery;
    burger_orders(orders, delivery);
    for (auto val : delivery) {
        cout << val << " ";
    }
    return 0;
}