//
// Anthony Sainez
// infiniteLoop.cpp
//

#include <string>   // for strings
#include <iostream> // for cin and cout
using namespace std;

int main()
{
    // Here's the while loop requirement of the exercise.
    while (true)
    {

        // The try/catch loop will ensure that this program runs in an infinite loop regardless
        // of what the user enters. This is called exception handling. So, the user can enter
        // in values that are not necessarily accounted for by the if-else chain.

        try
        {
            string input;
            cout << "Type in a word! If it's special, you'll know: ";
            cin >> input;
            cout << endl;

            // Here's an example if-else chain. You could achieve the same thing with a
            // switch and case statement. It is nearly the same thing.
            // Using a switch statement could simplify things: it would eliminate the need
            // for exception handling since you could use the `default` parameter.
            if (input == "42")
            {
                cout << "42 is the magic number!\n";
            }
            else if (input == "b")
            {
                cout << "You entered the letter b, which prompted this response!\n";
            }
            else if (input == "continue")
            {
                cout << "You want to continue? Sure thing!\n";
            }
            else if (input == "exit")
            {
                break;
            }
        }
        catch (const std::runtime_error &e)
        {
            // What this means is that any runtime error is caught and handled by simply
            // trying the loop again. So in other words, any time there's an exception, the
            // program will simply restart.
            continue;
        }
    }

    // Return 0 exits the program and is only reachable when the user inputs "exit" and breaks
    // the while(true) loop.
    return 0;
}
