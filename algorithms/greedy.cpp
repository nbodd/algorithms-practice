//
//  greedy.cpp
//  algorithms
//
//  Created by Nick on 2/5/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <stdint.h>
#include <queue>

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

// largest permutation
int largest_permutation_main() {
    // wrong answer, dont use
    unsigned long long N, K;
    cin >> N >> K;
    
    vector<int> A;
    vector<unsigned long long> countOfNum(10);
    vector<int> index(10, 0);
    for (int i=0; i<N; ++i) {
        int val;
        cin >> val;
        A.push_back(val);
        countOfNum[val]++;
        index[val] = i;
    }
    
    queue<int> swappedElements;
    vector<int> result;
    int traverse = 0;
    // greedy here
    while (K > 0 && traverse < N) {
        for (int digit = 9; digit >= 0; --digit) {
            if (countOfNum[digit] > 0) {
                
                if (A[traverse] != digit) {
                    break;
                }
                
                result.push_back(digit);
                swappedElements.push(A[traverse]);
                
                countOfNum[digit]--;
                K--;
                break;
            }
        }
        traverse++;
    }
    
    //add remaining elements in sequential order
    while (traverse < N) {
        int digit = A[traverse];
        if (countOfNum[digit] > 0) {
            result.push_back(digit);
            countOfNum[digit]--;
        } else {
            result.push_back(swappedElements.front());
            swappedElements.pop();
        }
        traverse++;
    }
    
    for (auto val : result) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}

class CutStyle {
public:
    bool row;
    unsigned long long cutCost;
    int cutIndex;
    
    CutStyle(int cost, int index, bool _row = true)
        : row(_row),
        cutCost(cost),
        cutIndex(index)
    {
        
    }
    
    CutStyle(const CutStyle& other) {
        row = other.row;
        cutCost = other.cutCost;
        cutIndex = other.cutIndex;
    }
};

bool CutStyleCompare(const shared_ptr<CutStyle> a, const shared_ptr<CutStyle> b) {
    return a->cutCost > b->cutCost;
}

int square_board_cuts() {
    int testCases;
    cin >> testCases;
    for (int i=0; i<testCases; ++i) {
        int m, n;
        cin >> m >> n;
        
        vector<shared_ptr<CutStyle>> cuts;
        
        for (int j=0; j<m-1; ++j) {
            int cost;
            cin >> cost;
            auto cut = make_shared<CutStyle>(cost, j, true);
            cuts.push_back(cut);
        }
        
        for (int j=0; j<n-1; ++j) {
            int cost;
            cin >> cost;
            auto cut = make_shared<CutStyle>(cost, j, false);
            cuts.push_back(cut);
        }
        
        // greedy - sort them
        std::sort(cuts.begin(), cuts.end(), CutStyleCompare);
        
        // greedy - pick the expensive one and cut
        int rowCuts = 0;
        int colCuts = 0;
        
        int64_t result = 0;
        for (int currentCutIndex = 0; currentCutIndex < cuts.size(); ++currentCutIndex) {
            const auto& currentCut = cuts[currentCutIndex];
            
            int previousCuts = 0;
            if (currentCut->row) {
                previousCuts = colCuts;
                rowCuts++;
            } else {
                previousCuts = rowCuts;
                colCuts++;
            }
            
            result += (previousCuts + 1) * currentCut->cutCost;
        }
        
        result %= ((int64_t) std::pow(10, 9) + 7);
        cout << result << endl;
    }
    return 0;
}


