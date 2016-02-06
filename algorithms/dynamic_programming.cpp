
#include <iostream>
#include <vector>

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

int main() {
    int testCases;
    cin >> testCases;
    
    for (int i=0; i<testCases; ++i) {
        int N;
        cin >> N;
        
        vector<int> elements;
        for (int j=0; j<N; ++j) {
            int val;
            cin >> val;
            elements.push_back(val);
        }
        cout << maximum_contiguous_subarray_sum(elements) << " " <<
            maximum_noncontiguous_subarray_sum(elements) << endl;
    }
    
    return 0;
}