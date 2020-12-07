//
//  binarySearch.cpp
//
//  Created by Anthony Sainez on 2 September 2020.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook.
//      *   I implemented some old code I had from a different class,
//          where I used a recursive binary search. Adapting it over
//          for this class was super easy. Here's the code:
//          https://github.com/tsainez/examples/blob/master/c%2B%2B/Recursion.cpp
//

#include<iostream>

using namespace std;

int binarySearch(int arr[], int low, int high, int key) {
    if (high < low)
        return -1;
    
    int mid = (low + high) / 2;
    
    if (key < arr[mid]) {
        return binarySearch(arr, low, mid - 1, key);
    } else if (key > arr[mid]) {
        return binarySearch(arr, mid + 1, high, key);
    }
    
    return mid;
}

int main() {
    int n, key;
    cin >> n;
    cin >> key;
    
    int* arr = new int[n];
    
    for(int i =0; i < n; i++)
        cin >> arr[i];
    
    cout << binarySearch(arr, 0, n, key);
    
    return 0;
}

