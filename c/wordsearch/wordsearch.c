//
//  wordsearch.c
//
//
//  Created by Anthony Sainez on 2/29/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// DO NOT INCLUDE OTHER LIBRARY!

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

/// Helper Functions
int searchHorizontal(char** arr, int n, char* word);
int searchVertical(char** arr, int n, char* word);
int searchDiagnolTLBR(char** arr, int n, char* word);
int searchDiagnolBLTR(char** arr, int n, char* word);

// Main function, DO NOT MODIFY!!!
int main(int argc, char **argv) {
    int bSize = 15;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
    char **words = (char**)malloc(50 * sizeof(char*));
    
    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }
    
    // Read puzzle block into 2D arrays
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));
        
        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
    fclose(fptr);
    
    // Open file for reading word list
    fptr = fopen("states.txt", "r");
    if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
    
    // Save words into arrays
    for(i=0; i<50; i++){
        *(words+i) = (char*)malloc(20 * sizeof(char));
        fgets(*(words+i), 20, fptr);
    }
    
    // Remove newline characters from each word (except for the last word)
    for(i=0; i<49; i++){
        *(*(words+i) + strlen(*(words+i))-2) = '\0';
    }
    
    // Print out word list
    printf("Printing list of words:\n");
    for(i=0; i<50; i++){
        printf("%s\n", *(words + i));
    }
    printf("\n");
    
    // Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
    printf("\n");
    
    // Call searchPuzzle to find all words in the puzzle
    searchPuzzle(block, bSize, words, 50);
    printf("\n");
    
    // Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
    printf("\n");
    
    return 0;
}

void printPuzzle(char** arr, int n){
    // This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
    // Your implementation here
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            // arr[i][j] == *(*(arr+i)+j)
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

void searchPuzzle(char** arr, int n, char** list, int listSize){
    // This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
    // Your implementation here
    int found = 0;
    for(int i=0; i < listSize; i++){
        // Check each search method through the list of words.
        // If a word is found, it will return true, and automatically
        // convert to lowercase.
        if(searchHorizontal(arr, n, *(list+i) ) ||
           searchVertical(arr, n, *(list+i) ) ||
           searchDiagnolTLBR(arr, n, *(list+i) ) ||
           searchDiagnolBLTR(arr, n, *(list+i) )
           ) {
            // This part is actually not necessary and can be entirely omitted.
            printf("Word found: %s\n", *(list+i) );
            found++;
        }
    } // end for
    
    // Verification Process
    // This bit here is very useful for bug checking.
    if(found > 0) {
        printf("\nNumber of words found: %d\n", found);
    } else {
        printf("\nNo words found.\n");
    }
}

void changeCase(char** arr, int wordSize, int row, int col, int type){
    /*
     // This function I wrote initially doesn't help very much...
     char* p;
     char* result;
     result = (char*)malloc(1+strlen(str));
     strcpy(result, str);
     for(p = result; *p != '\0'; p++) {
     // A = 65, a = 97, z = 90, z = 122
     if (*p >= 'A' && *p <= 'Z') {
     *p -= 32; //
     }
     }
     return result;
     */
    
    switch(type){
        case 1: // Horizontal
            for(int i = col; i < col+wordSize; i++) {
                if(*(*(arr+row)+i) >= 97) {
                    *(*(arr+row)+i) = *(*(arr+row)+i); // No change!
                } else {
                    *(*(arr+row)+i) = (char)(*(*(arr+row)+i)+32);
                    // changeCase_name(arr[row], i);
                }
            }
            break;
        case 2:  // Vertical
            for(int i = row; i < row+wordSize; i++) {
                if(*(*(arr+i)+col) >= 97) {
                    *(*(arr+i)+col) = *(*(arr+i)+col);
                } else {
                    *(*(arr+i)+col) = (char)(*(*(arr+i)+col)+32);
                }
            }
            break;
        case 3:   // TL->BR
            for(int i = 0; i < wordSize; i++) {
                if(*(*(arr+row+i)+col+i) >= 97) {
                    *(*(arr+row+i)+col+i) = *(*(arr+row+i)+col+i);
                } else {
                    *(*(arr+row+i)+col+i) = (char)(*(*(arr+row+i)+col+i)+32);
                }
            }
            break;
        case 4:   // BL->TR
            for(int i = 0; i < wordSize; i++) {
                if(*(*(arr+row-i)+col+i) >= 97) {
                    *(*(arr+row-i)+col+i) = *(*(arr+row-i)+col+i);
                } else {
                    *(*(arr+row-i)+col+i) = (char)(*(*(arr+row-i)+col+i)+32);
                }
            }
            break;
    }
}

/*
 
 void changeCase_by_ref(char** n) {
 *n = changeCase(*n);
 }
 
 void changeCase_name(char* names[], int i) {
 changeCase_by_ref(&(names[i]));
 }
 
 */

int searchHorizontal(char** arr, int n, char* word){
    // Type 1
    int size = strlen(word);
    
    for(int i = 0; i<n; i++) {
        for(int j = 0; j < n-size; j++) {
            int index = 0;
            while(index < size) {
                char a, b;
                
                if(*(word+index) >= 97) {
                    a = *(word+index);
                } else {
                    a = (char)(*(word+index)+32);
                }
                
                if(*(*(arr+i)+index+j) >= 97) {
                    b = *(*(arr+i)+index+j);
                } else {
                    b = (char)(*(*(arr+i)+index+j)+32);
                }
                
                if(a == b) { // Characters match
                    if(index == size-1) { // Check last character
                        changeCase(arr, size, i, j, 1);
                        return 1; // Found it!
                    }
                } else {
                    break;
                }
                
                index++;
            } // end while
        } // end second for
    } // end first for
    return 0;
} // end searchHorizontal

int searchVertical(char** arr, int n, char* word){
    // Type 2
    int size = strlen(word);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-size; j++){
            int index=0;
            while(index<size){
                char a, b;
                
                if(*(word+index) >= 97) {
                    a = *(word+index);
                } else {
                    a = (char)(*(word+index)+32);
                }
                
                if(*(*(arr+index+j)+i) >= 97) {
                    b = *(*(arr+index+j)+i);
                } else {
                    b = (char)(*(*(arr+index+j)+i)+32);
                }
                
                if(a==b) { //found character matching
                    if(index == size-1) { //last character
                        changeCase(arr, size, j, i, 2);
                        return 1; // Found it!
                    }
                } else {
                    break;
                }
                index++;
            } // end while
        } // end second for
    } // end first for
    
    return 0;
} // end searchVertical

int searchDiagnolTLBR(char** arr, int n, char* word){
    // Type 3
    int size = strlen(word);
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int index=0;
            while(index<size && (i+index<n) && (j+index<n)){
                char a, b;
                
                if(*(word+index) >= 97) {
                    a = *(word+index);
                } else {
                    a = (char)(*(word+index)+32);
                }
                
                if(*(*(arr+i+index)+j+index) >= 97) {
                    b = *(*(arr+i+index)+j+index);
                } else {
                    b = (char)(*(*(arr+i+index)+j+index)+32);
                }
                if(a==b){ // Match character
                    if(index == size-1){ // Last character
                        changeCase(arr, size, i, j, 3);
                        return 1; // Found it!
                    }
                } else {
                    break;
                }
                index++;
            }
        }
    }
    
    return 0;
}

int searchDiagnolBLTR(char** arr, int n, char* word){
    // Type 4
    int size = strlen(word);
    
    for(int i = n-1; i > 0; i--){
        for(int j = 0; j < n; j++){
            int index = 0;
            while(index<size && (i-index>0) && (j+index<n)){
                char a, b;
                
                if(*(word+index) >= 97) {
                    a = *(word+index);
                } else {
                    a = (char)(*(word+index)+32);
                }
                
                if(*(*(arr+i-index)+j+index) >= 97) {
                    b = *(*(arr+i-index)+j+index);
                    
                } else {
                    b = (char)(*(*(arr+i-index)+j+index)+32);
                }
                
                if(a==b){ // Character match
                    if(index == size-1){ // Last character
                        changeCase(arr, size, i, j, 4);
                        return 1; // Found it!
                    }
                } else {
                    break;
                }
                index++;
            }
        }
    }
    
    return 0;
}
