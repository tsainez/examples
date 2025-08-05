//
// Anthony Sainez
// printArea.cpp
//

#include <iostream>
using namespace std;

int main()
{
    float radius;
    const float pi = 3.14159;

    cout << "Please enter the radius of a circle: ";
    cin >> radius;

    cout << "The area of that circle is: " << pi * radius * radius << endl;

    return 0;
}
