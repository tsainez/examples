//
// arrCopy.c
// 
// Created by Anthony Sainez on 13 February 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for malloc

void printArr(int *a, int size){
    printf("Printing an array...\n");
	for(int i = 0; i <= size; i++) {
		printf("array[%d] = %d\n", i, *(a+i));
	}
}

int* arrCopy(int *a, int size){
    int *newArr = (int *)malloc(size * sizeof(int)); // dynamically init a new array
    for(int i = 0; i <= size; i++) {
        *(newArr+i) = *(a+i);
    }
    return newArr;
}


int main(){
    int n;
    int *arr;
    int *arr_copy;
    int i;
    printf("Enter size of array:\n");
    scanf("%d", &n);

    //Dynamically create an int array of n items
    arr = (int *)malloc(n * sizeof(int));
    
    //Ask user to input content of array
    for(i = 0; i <= n; i++) {
        printf("Input content of array[%d]:\n", i);
        scanf("%d", (arr+i));
    }
    
/*************** YOU MUST NOT MAKE CHANGES BEYOND THIS LINE! ***********/
	
	//Print original array
    printArr(arr, n);

	//Copy array
    arr_copy = arrCopy(arr, n);

	//Print new array
    printArr(arr_copy, n);

    return 0;
}
