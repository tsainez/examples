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

	/*
	int i;
	double* p;	// We use this reference variable to access
			// dynamically created array elements

	p = calloc(10, sizeof(double)); // Make double array of 10 elements
	
	for (i=0; i<10; i++)
		*(p + i) = i;
	
	for (i=0; i<10; i++)
		printf("*(p+%d) = %lf\n", i, *(p+i));

	free(p);

	putchar('\n');
	
	p = calloc(4, sizeof(double)); // make a new double array of 4 elements

	// notice the size has changed

	for (i=0; i<4; i++)
		*(p+i)=i*i; // put value i*i in array element i

	for (i=0; i<4; i++)
		printf("*(p+%d)=%lf\n", i, *(p+i));

	free(p);
	*/
	/*
	while(number != 0) {
		printf("Enter a number: ")
			
	} */
}
