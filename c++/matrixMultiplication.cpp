//
//  matrixMultiplication.cpp
//
//  Created by Anthony Sainez on 30 November 2020.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//
//  Sources Used
//      *   I used the textbook, notes taken during the lectures,
//          companion material from the textbook.
//      *   https://www.geeksforgeeks.org/double-pointer-pointer-pointer-c/
//          For help in figuring out how to manage my pointers and arrays.
//          For some reason, getting it to work with the normal arr[][] brackets
//          notation was frustratingly not working.
//      *   I sought out some help from the ACM discord members. They helped me
//          with the notation of this particular lab. I do not know who they were,
//          as their names were anonymous.
//

#include <iostream>
#include <climits>

using namespace std;

void printMatrices(int** s, int i, int j) {
    if (i == j) {
        cout << "A" << i - 1;
    } else {
        cout << "(";
        printMatrices(s, i, s[i - 1][j - 1]);
        printMatrices(s, s[i - 1][j - 1] + 1, j);
        cout << ")";
    }
}

void matrixChainOrder(int arr[], int n) {
    int j, q;
    
    int** m = new int*[n];
    
    for (int i = 0; i < n; i++)
        m[i] = new int[n];
    
    int** s = new int*[n - 1];
    
    for (int i = 0; i < n; i++)
        s[i] = new int[n];
    
    for (int i = 0; i < n; i++)
        m[i][i] = 0;

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            m[i - 1][j - 1] = INT_MAX;
            
            for (int k = i; k <= j - 1; k++) {
                q = (m[i - 1][k - 1] + m[k][j - 1]
                    + (arr[i - 1] * arr[k] * arr[j]));
                
                if (q < m[i - 1][j - 1]) {
                    m[i - 1][j - 1] = q;
                    s[i - 1][j - 1] = k;
                }
            }
        }
    }
    
    cout << m[0][n-1] << endl;
    
    printMatrices(s, 1, n);
    
    cout << endl;
}

int main() {
    int n;
    
    cin >> n;
    int* arr = new int[n + 1];
    
    for (int i = 0; i <= n; i++)
        cin >> arr[i];
    
    matrixChainOrder(arr, n);
    
    return 0;
}
