//
// Anthony Sainez
// functions.cpp
//

#include "functions.h"
#include <iostream> // Needed for `cout`
using namespace std;

// These functions are mostly self-explanatory.
void voidfunc1()
{
    cout << "void voidfunc()" << endl;
    cout << "Takes no argument." << endl;
    cout << endl;
}

int intfunc1(int i)
{
    cout << "int intfunc(int i)" << endl;
    cout << "Takes in an int argument." << endl;
    cout << "The argument submitted was: " << i << "\n";
    cout << endl;
}

char charfunc1(char c)
{
    cout << "char charfunc(char c)" << endl;
    cout << "Takes in a char argument." << endl;
    cout << "The argument submitted was: " << c << "\n";
    cout << endl;
}

float floatfunc1(float i)
{
    cout << "float floatfunc(float i)" << endl;
    cout << "Takes in a float argument." << endl;
    cout << "The argument submitted was: " << i << "\n";
    cout << endl;
}
