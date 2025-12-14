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

/**
 * Recursively prints the optimal parenthesization of the matrix chain product.
 *
 * @param s The split table computed by matrixChainOrder.
 * @param i The starting matrix index.
 * @param j The ending matrix index.
 */
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

/**
 * Computes the optimal order of matrix chain multiplication.
 *
 * Uses dynamic programming to find the minimum number of scalar multiplications
 * needed to compute the product of a chain of matrices.
 *
 * @param arr An array of dimensions where matrix A_i has dimensions arr[i-1] x arr[i].
 * @param n The number of matrices.
 */
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

/**
 * Main function to solve the Matrix Chain Multiplication problem.
 *
 * Reads the number of matrices and their dimensions from stdin,
 * then calculates and prints the minimum cost and optimal parenthesization.
 *
 * @return 0 on success.
 */
int main() {
    int n;
    
    cin >> n;
    int* arr = new int[n + 1];
    
    for (int i = 0; i <= n; i++)
        cin >> arr[i];
    
    matrixChainOrder(arr, n);
    
    return 0;
}
