//
//  pointers.c
//
//  Created by Anthony Sainez on 27 January 2020
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

#import <stdio.h>

void addOne (int *p) {
    *p = *p + 1;
}

/*
 void f() {
     int *ptr;
     *ptr = 5;
 }
 
 This code will assign 5 to a random memory address, so long as it's valid.
 Otherwise, it will return a segmentation fault.
*/

int main() {
    int x, y, *px, *py;
    int n = 10; // n stands for number of elements
    int array[n];
    
    // Practice manipulating pointers.
    printf("The value of x is %d\n", x);
    printf("The value of y is %d\n", y);
    printf("The value of array[0] is %d\n", array[0]);
    
    printf("\n");
    x = 3;
    y = 4;
    array[0] = 5;
    
    printf("The value of x is now %d\n", x);
        printf("The value of y is now %d\n", y);
        printf("The value of arr[0] is now %d\n", array[0]);
    
    printf("\n");
    printf("The address of x is %p\n", &x);
    printf("The address of y is %p\n", &y);
    printf("The address of arr[0] is %p\n", &array[0]);
    
    printf("\n");
    px = &x;
    py = &y;
    
    printf("px now points to x, which is at %p\n", px);
    printf("py now points to y, which is at %p\n", py);
    printf("The address of px is %p\n", &px);
    printf("The address of py is %p\n", &py);

    for(int i = 0; i < n; i++) {
        printf("array[%d] = %d\n", i, *(array+i));
    }
    
    printf("array points to array[0], whose address is %p\n", array);
    printf("The address of array[0] is %p\n", &array[0]);

    printf("The address of array is %p\n", &array);

    return 0;
}
