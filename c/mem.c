
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> // for malloc

int main() {
    int num;
    int *ptr;
    int **handle;
    
    num = 14;
    ptr = (int *)malloc(2 * sizeof(int));
    *ptr = num;
    handle = (int **)malloc(1 * sizeof(int *));
    *handle = ptr;
    
    // Insert extra code here
    printf("num address: %p\n", &num);
    printf("ptr address: %p\n", &ptr);
    printf("*ptr address: %p\n", &(*ptr));
    printf("handle address: %p\n", &handle);
    printf("*handle address: %p\n", &(*handle));
    printf("**handle address: %p\n", &(**handle));
    
    printf("ptr returns: %p\n", ptr);
    printf("*ptr returns: %d\n", *ptr);
    
    free(ptr);
    free(handle);
    
    return 0;
} 

