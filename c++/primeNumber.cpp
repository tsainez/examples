//
// Anthony Sainez
// primeNumber.cpp
//

#include <iostream>
using namespace std;

int main()
{
    int input;
    cout << "Up to what number would you like to see primes?: ";
    cin >> input;

    cout << "The prime numbers are: ";

    for (int i = 0; i <= input; i++)
    {
        // Skip 0 and 1 as they are not prime numbers.
        if (i == 1 || i == 0)
            continue;

        // flag variable to tell if i is prime or not.
        bool flag = 1;

        // Iterate to check if i is prime or not
        for (int j = 2; j <= i / 2; ++j)
        {
            if (i % j == 0)
            {
                flag = 0;
                break;
            }
        }

        // 1 = true, 0 = false, we only want to print when true.
        if (flag)
            cout << i << " ";
    }

    cout << endl; // This endl is here to cap off the final print statement so that there are no errors.

    return 0;
}
