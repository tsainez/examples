//
// MatrixMult.c
//
// Created by Anthony Sainez on 24 February 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>

int** matMult(int **a, int **b, int size){
    // (4) Implement your matrix multiplication here. You will need to create a new matrix to store the product.
    int **mul;
    mul = (int **)malloc(size * sizeof(int *));
    int sum = 0;
    
    for(int i = 0; i < size; i++) {
        mul[i] = (int *)malloc(size * sizeof(int));
    }
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                sum = sum + a[i][k] * b[k][j];
            } // end k
            mul[i][j] = sum;
            sum = 0;
        } // end j
    } // end i
    return mul;
}

void printArray(int **arr, int n){
    // (2) Implement your printArray function here
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("[%d]",arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 3, count = 0;
    int **matA, **matB, **matC;
    // (1) Define 2 n x n arrays (matrices).
    // The following process could be made cleaner with the use of functions.
    matA = (int **)malloc(n * sizeof(int *));
    
    for(int i = 0; i < n; i++) {
        matA[i] = (int *)malloc(n * sizeof(int));
    }
    
    matB = (int **)malloc(n * sizeof(int *));
    
    for(int i = 0; i < n; i++) {
        matB[i] = (int *)malloc(n * sizeof(int));
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matA[i][j] = ++count;
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matB[i][j] = ++count;
        }
    }
    
    // (3) Call printArray to print out the 2 arrays here.
    printf("matA = \n");
    printArray(matA, n);
    printf("matB = \n");
    printArray(matB, n);
    
    //(5) Call matMult to multiply the 2 arrays here.
    printf("matC = \n");
    matC = matMult(matA, matB, n);
    
    //(6) Call printArray to print out resulting array here.
    printArray(matC, n);
    
    
    return 0;
}
