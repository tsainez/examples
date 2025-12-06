#
#  integer-classification.py
#
#  Created by Anthony Sainez on 11 October 2019
#  Copyright © 2020 Anthony Sainez. All rights reserved.
#

"""
Performs basic integer classification and analysis tasks.

This script executes four problems:
1. Prompts for a name and prints a greeting.
2. Classifies an input integer as even or odd.
3. Finds the largest integer in a user-provided list of 10 integers.
4. Finds the largest odd integer in a user-provided list of 10 integers.
"""

def main():
    """
    Main function to execute the integer classification problems.
    """
    # problem 1, modified hello world
    print("Problem #1\n")
    name = input("What's your name?\n")
    print("Hello, " + name)

    #problem 2, integer classification
    print("\n-------------------------------")
    print("Problem #2\n")
    input_integer = input("Please input an integer\n")

    if (int(input_integer) %2) == 0:
        print("The integer " + input_integer + " is even.")
    else:
        print("The integer " + input_integer + " is odd.")

    #problem 3, largest integer
    print("\n-------------------------------")
    print("Problem #3\n")

    intArray = []

    for i in range(10):
        newValue = int(input("Please input intArray[" + str(i) + "]: "))
        intArray.append(newValue)

    maxValue = intArray[0] #assign random number
    for i in range(len(intArray)):
        if intArray[i]>maxValue:
            maxValue = intArray[i]

    print("The largest integer of intarray is " + str(maxValue))


    #problem 4, largest odd integer
    print("\n-------------------------------")
    print("Problem #4\n")

    intArrayOdd = []

    for i in range(10):
        newValue = int(input("Please input intArrayOdd[" + str(i) + "]: "))
        intArrayOdd.append(newValue)

    largest = 0 # arbitration
    for number in intArrayOdd:
        if number % 2 != 0 and number > largest:
            largest = number

    if largest == 0:
        print("There were no odd integers")
    else:
        print("The largest odd integer in the stack is " + str(largest) + ".")

if __name__ == "__main__":
    main()
