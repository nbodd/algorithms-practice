//
//  binary_search.cpp
//  algorithms
//
//  Created by Nick on 2/2/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include "binary_search.h"

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;


bool CompareByFirst(pair<int, int> & a, pair<int, int>& b) {
    return (a.second != b.second) && (a.first < b.first);
}

bool binary_search_first_key(vector<pair<int, int>> &choices, int min, int max, int key, pair<int, int>& result) {
    if (min > max) {
        return false;
    }
    
    int mid = (max + min)/2;
    
    auto& currentChoice = choices[mid];
    if (currentChoice.first > key) {
        return binary_search_first_key(choices, min, mid-1, key, result);
    } else if (currentChoice.first < key) {
        return binary_search_first_key(choices, mid+1, max, key, result);
    } else {
        // key is found
        result = currentChoice;
        return true;
    }
}

void ice_cream_parlor() {
    vector<pair<int, int>> choices;
    int money = 0;
    
    int totalChoices;
    cin >> money >> totalChoices;
    
    for (int choiceNumber = 0; choiceNumber < totalChoices; ++choiceNumber) {
        int choicePrice;
        cin >> choicePrice;
        
        if (choicePrice >= money) {
            continue;
        }
        
        choices.push_back(pair<int, int>(choicePrice, choiceNumber));
    }
    
    int choiceIndex = 0;
    std::sort(choices.begin(), choices.end(), CompareByFirst);
    for (int i=0; i<choices.size(); ++i) {
        int choicePrice = choices[i].first;
        int requiredPrice = money - choicePrice;
        choiceIndex = choices[i].second;
        
        //do binary search here
        pair<int, int> result;
        bool res = binary_search_first_key(choices, 0, (int) choices.size() - 1, requiredPrice, result);
        
        if (res) {
            if (choiceIndex == result.second) {
                continue;
            }
            
            if (choiceIndex < result.second) {
                cout << choiceIndex + 1 << " " << result.second + 1 << endl;
            } else {
                cout << result.second + 1 << " " << choiceIndex + 1 << endl;
            }
            break;
        }
    }
}

int main() {
    int testCases;
    cin >> testCases;

    for (int i=0; i<testCases; ++i) {
        ice_cream_parlor();
    }
    
    return 0;
}