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
    int *p, x; // *p stores the address of an integer, x stores an integer
    
    x = 3;
    
    p =&x; // p now stores the address of x, & gets the address of a variable
    
    printf("p points to %d\n", *p); // % is a flag, d refers to integer,
                                    // * is a derefernce operator, it gets the value pointed to
    
    int y = 4;
    
    *p = y; // reassignment of a pointer
    
    printf("p points to %d\n", *p);
    
    addOne(&y);
    
    printf("y is now %d\n", y);
    
    int *q = (int *) x; // casting
    printf("q points to %d\n", *q);

    return 0;
}
