//
// Created by Anthony Sainez on 10/2/20.
//
// Sources Used
//  *   I used the textbook, notes taken during the lectures,
//      companion material from the textbook.
//  *   http://www.cplusplus.com/reference/climits/
//  *   https://en.cppreference.com/w/cpp/algorithm/max
//  *   https://en.wikipedia.org/wiki/Maximum_subarray_problem

#include <iostream>
#include <climits>      // for INT_MIN
#include <algorithm>    // for std::max
using namespace std;

// Ripped directly from page 72 of the textbook psuedocode.
int maxCrossingSum(int array[], int low, int mid, int high) {
    int sum = 0;
    int left_sum = INT_MIN; // INT_MIN counts as negative infinity
    
    for (int i = mid; i >= low; i--) {
        sum = sum + array[i];
        
        if (sum > left_sum)
          left_sum = sum;
    }
  
    sum = 0;
    int right_sum = INT_MIN;
    
    // For some reason, mid++ doesn't work on my machine.
    // Will investigate later.
    for (int i = mid+1; i <= high; i++) {
        sum = sum + array[i];
        
        if (sum > right_sum)
          right_sum = sum;
    }
  
    return max({left_sum + right_sum, left_sum, right_sum});
}

// Ripped directly from page 72 of the textbook psuedocode.
int maxSubArraySum(int array[], int low, int high) {
   // Base Case: Only one element
   if (low == high)
     return array[low];
  
   // Find midpoint
   int mid = (low + high)/2;
  
   return max({maxSubArraySum(array, low, mid),
              maxSubArraySum(array, mid+1, high),
              maxCrossingSum(array, low, mid, high)});
}

int main() {
    int n;

    cin >> n;
    int* array = new int[n];

    for (int i = 0; i < n; i++)
        cin >> array[i];

    cout << maxSubArraySum(array, 0, n-1);

    return 0;
}
