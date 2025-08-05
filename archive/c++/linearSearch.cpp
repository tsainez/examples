//
//  linearSearch.cpp
//
//  Created by Anthony Sainez on 2 September 2020.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook. I lowkey just copied
//          the psuedocode and turned it into C++ code. It wasn't difficult.
//

#include <iostream>

using namespace std;

int linearSearch(int arr[], int n, int key) {
    for(int i=0; i < n; i++)
        if (arr[i] == key)
            return i;
    
    return -1;
}

int main() {
    int n, key;
    cin >> n;
    cin >> key;
    
    int* arr = new int[n];
    
    for(int i = 0; i < n; i++)
    cin >> arr[i];
    
    cout << linearSearch(arr, n, key);

    return 0;
}
