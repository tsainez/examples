//
// averages.c
//
// Created by Anthony Sainez on 22 January 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <stdio.h>

/*
   Read a set of values from the user.
    Store the sum in the sum variable and return the number of values read.
*/

int read_values(double *sum) {
  int values=0,input=0;
  *sum = 0;
  printf("Enter input values (enter 0 to finish):\n");
  scanf("%d",&input);
  while(input != 0) {
    values++;
    *sum += input;
    scanf("%d", &input);
  }
  return values;
}

int main() {
  double sum=0;
  int values;
  values = read_values(&sum);
  printf("Average: %.2f\n",sum/values);
  return 0;
}

