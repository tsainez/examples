//
// question1.cpp
// Anthony Sainez
//

// Create a struct that holds two string objects and one int.
// Use a typedef for the struct name. Create an instance of the
// struct, initialize all three values in your instance, and
// print them out. Take the address of your instance and assign
// it to a pointer to your struct type. Change the three values
// in your instance and print them out, all using the pointer.

#include <iostream>
#include <string>
using namespace std;

typedef struct bag
{
    string a, b;
    int c;
} bag;

int main()
{
    bag x;
    x.a = "Hello!";
    x.b = "World!";
    x.c = 1234;

    cout << "The bag object 'x' contains the values: " << x.a << ", " << x.b << ", " << x.c << endl;

    bag *y = &x;
    y->a = "!olleH";
    y->b = "!dlroW";
    y->c = 4321;
    cout << "The bag object 'y' contains the values: " << y->a << ", " << y->b << ", " << y->c << endl;
}