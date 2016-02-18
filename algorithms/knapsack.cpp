#include <iostream>
#include <vector>

using namespace std;

void knapsack() {
    int testCases;
    cin >> testCases;
    
    for (int test = 0; test < testCases; ++test) {
        int n, k;
        cin >> n >> k;
        
        vector<int> weights(n);
        for (int i=0; i<n; ++i) {
            cin >> weights[i];
        }
        
        vector<int> possibleValues(k+1);
        possibleValues[0] = 0;
        
        for (int i=0; i<= k; ++i) {
            vector<int> currentValues(n);
            
            for (int weightIndex= 0; weightIndex < weights.size(); ++weightIndex) {
                currentValues[weightIndex] = 0;
                if (i >= weights[weightIndex]) {
                    currentValues[weightIndex] = weights[weightIndex] + possibleValues[ i - weights[weightIndex]];
                }
            }
            
            possibleValues[i] = *max_element(currentValues.begin(), currentValues.end());
        }
        
        cout << possibleValues[k] << endl;
    }
}

int kp_main() {
    knapsack();
    return 0;
}