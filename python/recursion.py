#
#  recursion.py
#
#  Created by Anthony Sainez on 22 January 2020
#  Copyright © 2020 Anthony Sainez. All rights reserved.
#

"""
Demonstrates basic recursive algorithms in Python.

This module contains implementations of factorial, Fibonacci sequence,
and summation of a list using recursion.
"""

import sys
sys.setrecursionlimit(100000)

def factorial(n):
    """
    Calculates the factorial of a non-negative integer using recursion.

    Args:
        n (int): The non-negative integer to calculate the factorial of.

    Returns:
        int: The factorial of n.
    """
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

def fib(n):
    """
    Calculates the nth Fibonacci number using recursion.

    Note: This implementation assumes 1-based indexing where fib(1) = 0, fib(2) = 1.

    Args:
        n (int): The position in the Fibonacci sequence.

    Returns:
        int: The nth Fibonacci number. Returns None (implicitly) and prints an error for n < 0.
    """
    if n<0: 
        print("Incorrect input") 
    elif n==1: 
        return 0
    elif n==2: 
        return 1
    else: 
        return fib(n-1)+fib(n-2) 

def addup(list):
    """
    Calculates the sum of elements in a list using recursion.

    Args:
        list (list): A list of numbers.

    Returns:
        int or float: The sum of the numbers in the list.
    """
    if len(list) == 0:
        return 0
    else:
        return list[0] + addup(list[1:])

def main():
    """
    Main function to test the recursive functions.
    """
    print('factorial(5):', factorial(5))
    # Expected 120

    print('fib(8):', fib(8))
    # Expected 13

    print('addup([1,2,3,4,5]):', addup([1,2,3,4,5]))
    # Expected 15
    print('addup(range(101)):', addup(range(101)))
    # Expected 5050

if __name__ == "__main__":
    main()
