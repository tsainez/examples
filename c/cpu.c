//  Try running it like so to see something interesting!
//      gcc -o cpu cpu.c -Wall
//      ./cpu A & ; ./cpu B & ; ./cpu C & ; ./cpu D &     

// Simple Example: Code That Loops And Prints (cpu.c)
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
// #include "common.h"

int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }
    char *str = argv[1]
    while(1) {
        Spin(1);
        printf("%s\n", str);
    }
    return 0;
}