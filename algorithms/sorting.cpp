#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void printArray(vector<int>& arr) {
    for (int i=0; i<arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int insertionSort(vector<int>& ar) {
    int ar_size = (int) ar.size();
    if (ar_size <= 1) {
        return 0;
    }
    
    int count = 0;
    for (int i=1; i<ar_size; ++i) {
        int lastElement = ar[i];
        for (int j=i-1; j >= 0; --j) {
            if (ar[j] > lastElement) {
                ar[j + 1] = ar[j];
                ar[j] = lastElement;
                count++;
            }
        }
    }
    return count;
}


int partition(vector<int>& arr, int startIndex, int endIndex, int & count) {
    
    int pivot = arr[endIndex];
    
    int traverse = startIndex;
    int low = startIndex;
    while (traverse < endIndex) {
        if (arr[traverse] < pivot) {
            int temp = arr[low];
            arr[low] = arr[traverse];
            arr[traverse] = temp;
            low++;
            count++;
            //          printArray(arr);
        }
        traverse++;
    }
    
    int temp = arr[low];
    arr[low] = pivot;
    arr[endIndex] = temp;
    count++;
    //    printArray(arr);
    
    return low;
}

int quickSort(vector<int>& arr, int startIndex, int endIndex) {
    
    if (startIndex >= endIndex) {
        return 0;
    }
    
    int count = 0;
    int partitionIndex = partition(arr, startIndex, endIndex, count);
    
    count += quickSort(arr, startIndex, partitionIndex - 1);
    count += quickSort(arr, partitionIndex + 1, endIndex);
    
    return count;
}

int sorting_main()
{
    int n;
    cin >> n;
    
    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }
    
    vector<int> arr2(arr);
    int qck = quickSort(arr, 0, (int) arr.size() - 1);
    int ins = insertionSort(arr2);
    cout << ins - qck;
    
    return 0;
}

int counting_sort() {
    int n;
    cin >> n;
    int numOfTimes[100] = { 0 };
    vector<pair<int, string>> data;
    for (int i=0; i<n; ++i) {
        int val;
        cin >> val;
        string text;
        cin >> text;
        
        numOfTimes[val]++;
        data.push_back(pair<int, string>(val, text));
    }
    
    int incrementalPosition[100] = { 0 };
    int totalSum = 0;
    for (int i=0; i<100; ++i) {
        incrementalPosition[i] = totalSum;
        totalSum += numOfTimes[i];
    }
    
    //positionsOfData tracks location of each data item from 0..n-1 will be placed
    // positionOfData[i] -> i-th data member will be placed at the resulting value
    vector<int> positionsOfData(n);
    for (int i=0; i<n; ++i) {
        int incrementalPositionIndex =  data[i].first;
        positionsOfData[i] = incrementalPosition[incrementalPositionIndex];
        incrementalPosition[incrementalPositionIndex]++;
    }
    
    // reverse the positionsOfData vector
    // Because, when we want to print, we dont care where each data element is placed,
    // instead we want sequentially which data member is needed to be placed next
    vector<int> reversePositionData(positionsOfData.size());
    for (int i=0; i < positionsOfData.size(); ++i) {
        reversePositionData[positionsOfData[i]] = i;
    }
    
    for (int i=0; i<reversePositionData.size(); ++i) {
        int dataIndex = reversePositionData[i];
        cout << ((dataIndex >= n/2) ? data[dataIndex].second : "-") << " ";
    }
    cout << endl;
    
    return 0;
}
