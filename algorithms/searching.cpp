#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

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

int main() {
    missing_numbers();
    return 0;
}