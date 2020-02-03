//
// averages.c
//
// Created by Anthony Sainez on 22 January 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#import <stdio.h>

int main() {
	int num = 0;
	int posTotal = 0, posCount = 0;
	int negTotal = 0, negCount = 0;
	
	printf("Please enter an integer: ");
	scanf("%d", &num);	

	while (num != 0) {
		if(num > 0) {
			posTotal += num;
			posCount++;
        } else {
            if (num < 0) {
                negTotal += num;
                negCount++;
            }
		}

		printf("Please enter an integer: ");
		scanf("%d", &num);
	}

	if (posCount != 0) {
		printf("Positive average: %d \n", (posTotal / posCount));
	}
	
    if (negCount != 0) {
		printf("Negative average: %d \n", (negTotal / negCount));
	}

}
