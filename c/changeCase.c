//
// changeCase.c
//
// Created by Anthony Sainez on 25 February 2020
// Copyright © 2020 Anthony Sainez. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* changeCase(char* str) {
	char* p;
	char* result;
	result = (char*) malloc(1+strlen(str));
	strcpy(result, str);
	for(p = result; *p!='\0'; p++) {
		if(*p >= 'a' && *p <= 'z') {
			*p += 'A' - 'a';
		}
	}
	
	return result;
}

void changeCase_by_ref(char** n) {
	*n = changeCase(*n);
}

void changeCase_name(char* names[], int i) {
	changeCase_by_ref(&(names[i]));
}

int main(int argc, char **argv) {

}
