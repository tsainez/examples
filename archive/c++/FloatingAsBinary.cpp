// Modify FloatingAsBinary.cpp so that it prints out each part of the double as a separate group of bits. You’ll have to replace the calls to printBinary( ) with your own specialized code.

#include <cstdlib>
#include <iostream>
using namespace std;

unsigned const int CHAR_LENGTH = 8;

void printBinary(float x) {
    int i; // declare variables

    int bit = 0;

    int* b = reinterpret_cast<int*>(&x); // use reinterpret_cast function
    for (int k = 31; k >= 0; k--) // for loop to print out binary pattern
    {
        bit = ((*b >> k) & 1); // get the copied bit value shift right k times, then and with a 1.
        cout << bit; // print the bit.
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Must provide a number" << endl;
        exit(1);
    }
    double d = atof(argv[1]);

    printBinary(d);
}