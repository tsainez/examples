//
// MemCast.c
//
// Created by Anthony Sainez on 24 February 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <stdio.h>

int main() {
    int four_ints[4];
    char* four_c;
    
    for(int i=0; i<4; i++)
        four_ints[i] = 2;
    
    printf("%x\n", four_ints[0]); // 2
    
    four_c = (char*)four_ints;
    
    for(int i=0; i<4; i++)
        four_c[i] = 'A'; // ASCII value of 'A' is 65 or 0x41 in Hex.
    
    // Add your code for the exercises here:
    printf("four_ints[0]:%x\n",four_ints[0]); // 41414141
    printf("four_ints[1]:%x\n\n",four_ints[1]); // 2
    
    printf("address of four_ints:%p\n",four_ints); // 0x7ffeee9d1b50
    printf("address of four_c:%p\n\n",four_c); // 0x7ffeee9d1b50
    
    for(int i=0; i<4; i++){
        printf("address of four_int[%d]:%p\n", i,&four_ints[i]);
        printf("four_int[%d]:%x\n", i,&four_ints[i]);
        // we use x instead of p so that it prints a hex number
        // and not the address of a pointer.
    }
    printf("\n");
    
    for(int i=0; i<4; i++){
        printf("address of four_c[%d]:%p\n",i,&four_c[i]);
        printf("four_c[%d]:%x\n", i,&four_c[i]);
    }
    
    printf("\n");
    return 0;
}
