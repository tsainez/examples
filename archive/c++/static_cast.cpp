//
// Anthony Sainez
// question2.cpp
//

// Define an array of int. Take the starting address of that array
// and use static_cast to convert it into a void*. Write a function
// that takes a void*, a number (indicating a number of bytes), and
// a value (indicating the value to which each byte should be set)
// as arguments. The function should set each byte in the specified
// range to the specified value. Try out the function on your array
// of int.

#include <iostream>

using namespace std;

void printArray(int* ptr, const int n) {
    cout << "array's contents are...\n";
    for (int i = 0; i < n; i++) {
        cout << "value `" << *(ptr + i) << "`\tat `" << ptr + i << "`\n";
    }
    cout << endl;
}

void modifyValues(void* vPtr, int count, int val) {
    // Count manages the range (how many bytes?)
    int* intPtr = static_cast<int*>(vPtr);
    for (int i = 0; i < count; i++) {
        *(intPtr + i) = val;
    }
}

int main() {
    int n = 5;
    int foo[n] = {}; // empty array

    void* vPtr = static_cast<void*> (foo);

    printArray(foo, n);
    modifyValues(vPtr, 2, 5);
    printArray(foo, n);

    return 0;
}