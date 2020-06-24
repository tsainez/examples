//
// fizzbuzz.c
//
// Created by Anthony Sainez on 23 June 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    for(int i = 0; i <= 32; i++) {
        if (i % 3 == 0) {
            printf("Fizz! %d\n", i);
        } else if (i % 5 == 0) {
            printf("Buzz! %d\n", i);
        }

    }
    return 0;
}
