//
// Anthony Sainez
// Fillvector.cpp
//

//: C02:Fillvector.cpp
// Copy an entire file into a vector of a string
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    //    vector<string> v;
    ifstream in("Fillvector.cpp");
    string line;
    string total;
    while (getline(in, line))
        total += line;

    //        v.push_back(line); // Add the line to the end
    // Add line numbers:
    //    for(int i = 0; i < v.size(): i++)
    //        cout << i << ": " << v[i] << endl;

    cout << total;
} ///:~
