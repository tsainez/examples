//
//  bucketSort.cpp
//
//  Created by Anthony Sainez on 6 October 2020.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook.
//      *   Using vectors to represent the buckets was significantly easier.
//      *   I updated the assignment to include my own insertion sort function
//          which was written to take in a vector input instead of using
//          the standard algorithm library. It may be less readable, but it's
//          correct.
//

#include <iostream>
#include <vector>
using namespace std;

// Modified from a previous assignment, originally made by me
// on 9/2/20. The & indicates address, which I learned from CSE 031 in C.
void insertionSort(vector<double> &arr) {
    if (arr.size() == 0) {
        return; // terminate early
    } else {
        for(int i = 0; i < arr.size() - 1; i++) {
            int j = i + 1;
            
            // If you wanted to reverse the order of sorting,
            // you can change the sign of the second condition.
            while (j > 0 && arr[j - 1] > arr[j]) {
                swap(arr[j-1], arr[j]);
                j--;
            }
        }
    }
}
  
// From CLRS page 201
void bucketSort(double arr[], int n) {
    vector<double> bucket[n];
  
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];
        bucket[bi].push_back(arr[i]);
    }
  
    for (int i = 0; i < n; i++)
        insertionSort(bucket[i]);
  
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < bucket[i].size(); j++)
            arr[index++] = bucket[i][j];
}
  
int main() {
    int n;
    cin >> n;
    
    double arr[n];
    
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    
    bucketSort(arr, n);
    
    for(int i = 0; i < n; i++)
        cout << arr[i] << endl;
        
    return 0;
}
