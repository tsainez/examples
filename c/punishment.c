// 
// punishment.c
//
// Created by Anthony Sainez on 30 January 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#import <stdio.h>

int main() {
    int num, typo;
    
    printf("Enter the number of lines for the punishment: ");
    scanf("%d", &num);
    
    if(num < 0) {
        printf("You entered an incorrect value for the number of lines!\n");
        return 1;
    } else {
        printf("Enter the line for which we want to make a typo: ");
        scanf("%d", &typo);
        
        if(typo < 0 || typo > num) {
            printf("You entered the incorrect value for the typo.\n");
            return 1;
        } else {
            for(int i = 1; i <= num; i++) {
                if(i != typo) {
                    printf("C Programming Language is the best!\n");
                } else {
                    printf("C Programming Language is the bet!\n");
                }
            }
        }
    }
    return 0;
}
