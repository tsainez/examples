//
// swapArray.c
//
// Created by Anthony Sainez on 25 February 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void swapArray(int* a1, int* a2, int size) {
    int *temp = (int *)malloc(size * sizeof(int));
    
    for(int i = 0; i < size; i++) {
        *(temp+i) = *(a1+i);
        *(a1+i) = *(a2+i);
        *(a2+i) = *(temp+i);
    }
}

void printArr(int *a, int size) {
    for(int i = 0; i < size; i++) {
        printf("array[%d] = %d\n", i, *(a+i));
    }
}

int main(int argc, char **argv) {
    int *arr1, *arr2;
    
    int n = 4; // arbitrary
    arr1 = (int *)malloc(n * sizeof(int));
    arr2 = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        printf("Input content of arr1[%d]:\n", i);
        scanf("%d", (arr1+i));
    }
    
    for (int i = 0; i < n; i++) {
        printf("Input content of arr2[%d]:\n", i);
        scanf("%d", (arr2+i));
    }
    
    swapArray(arr1, arr2, n);
    
    printArr(arr1, n);
    printArr(arr2, n);
}
