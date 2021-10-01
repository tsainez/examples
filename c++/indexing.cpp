// Write a function that takes a char* argument. Using new, dynamically allocate an array of char that is the size of the char array that’s passed to the function. Using array indexing, copy the characters from the argument to the dynamically allocated array (don’t forget the null terminator) and return the pointer to the copy. In your main( ), test the function by passing a static quoted character array, then take the result of that and pass it back into the function. Print both strings and both pointers so you can see they are different storage. Using delete, clean up all the dynamic storage.

#include <iostream>
#include <cstring>
using namespace std;

char* copy(char* s1) {
    int len = strlen(s1);
    char* s2 = new char[len + 1];
    strcpy(s2, s1);
    return s2;
}

int main() {
    char* first = "Hello world";
    char* second = copy(first);

    cout << "1 == `" << first << "` at " << static_cast<void*>(first) << endl;
    cout << "2 == `" << second << "` at " << static_cast<void*>(second) << endl;

    // The static cast above is necessary because the output stream insertion operator is overloaded to treat a char* as a null-terminated string. All other points have their addresses printed out in hexadecimal.

    delete[] second;
}