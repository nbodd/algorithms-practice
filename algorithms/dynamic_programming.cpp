
#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

void fib_modified() {
    int A, B;
    cin >> A >> B;
    
    int N;
    cin >> N;
    
    vector<unsigned long long> fb;
    fb.push_back(A);
    fb.push_back(B);
    for (int i=2; i<N; ++i) {
        fb.push_back(fb[i-1] * fb[i-1] + fb[i-2]);
    }
    
    cout << fb[fb.size() - 1 ] << endl;
}

int maximum_contiguous_subarray_sum(vector<int> & elements) {
    vector<int> sum(elements.size());
    
    sum[0] = elements[0];
    for (int i=1; i<elements.size(); ++i) {
        sum[i] = max(sum[i-1] + elements[i], elements[i]);
    }
    
    return *max_element(sum.begin(), sum.end());
}

int maximum_noncontiguous_subarray_sum(vector<int> & elements) {
    vector<int> sum(elements.size());
    
    sum[0] = elements[0];
    for (int i=1; i<elements.size(); ++i) {
        sum[i] = max(sum[i-1] + elements[i], sum[i-1]);
        sum[i] = max(sum[i], elements[i]);
    }
    
    return *max_element(sum.begin(), sum.end());
}

void coin_change_problem() {
    unsigned long long money, numOfCoins;
    cin >> money >> numOfCoins;
    
    vector<unsigned long long> coinValues(numOfCoins + 1);
    for (int i=1; i<numOfCoins + 1; ++i) {
        cin >> coinValues[i];
    }
    
    vector<vector<unsigned long long>> coinChangeGrid(money + 1);
    for (int i=0 ; i < money + 1; ++i) {
        coinChangeGrid[i] = vector<unsigned long long>();
        coinChangeGrid[i].resize(numOfCoins + 1);
    }
    
    for (int coin=0; coin < numOfCoins + 1; ++coin) {
        coinChangeGrid[0][coin] = 1;
    }
    
    for (int moneyValue=0; moneyValue <= money; ++moneyValue) {
        coinChangeGrid[moneyValue][0] = 0;
    }
    
    for (int moneyValue = 1; moneyValue <= money; ++moneyValue) {
        for (int coin = 1; coin <= numOfCoins; ++coin) {
            unsigned long long coinValue = coinValues[coin];
            if (moneyValue < coinValue) {
                coinChangeGrid[moneyValue][coin] = coinChangeGrid[moneyValue][coin-1];
            } else {
                coinChangeGrid[moneyValue][coin] = coinChangeGrid[moneyValue][coin-1] + coinChangeGrid[moneyValue - coinValue][coin];
            }
        }
    }
    
    cout << coinChangeGrid[money][numOfCoins] << endl;
}

int school_teacher_candies() {
    int N;
    cin >> N;
    
    vector<int> rating(N);
    for (int i=0; i<N; ++i) {
        cin >> rating[i];
    }
    
    vector<int> candies(N);
    candies[0] = 1;
    for (int i=1; i<N; ++i) {
        if (rating[i] > rating[i-1]) {
            candies[i] = candies[i-1] + 1;
        } else {
            candies[i] = 1;
        }
    }
    
    for (int j=N-1; j>0; --j) {
        if (rating[j-1] > rating[j] && candies[j-1] <= candies[j]) {
            candies[j-1] = candies[j] + 1;
        }
    }
    
    int sum = 0;
    for (auto val : candies) {
        sum += val;
    }
    cout << sum << endl;
    
}
