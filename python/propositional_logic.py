#
#  propositional_logic.py
#
#  Created by Anthony Sainez on 9 November 2019
#  Copyright © 2020 Anthony Sainez. All rights reserved.
#

"""
Demonstrates the use of the `truth_table_generator` module.

This script solves two problems:
1. Generates basic truth tables for common logical connectives.
2. Checks for equivalence between two user-provided propositional logic formulas.
"""

from truth_table_generator import TruthTable

def main():
    """
    Main function to execute the propositional logic demonstrations.
    """
    # problem 1, basic truth tables
    print("Problem #1\n")

    myTable = TruthTable(['a', 'b'], ['-a', 'a and b', 'a or b', 'a -> b', 'a <-> b'])
    myTable.display()

    # problem 2, equivalence in propositional logic
    print("\n-------------------------------")
    print("Problem #2\n")

    prop_1 = input("Enter proposition 1: ")
    prop_2 = input("Enter proposition 2: ")

    equivalenceTable = TruthTable(['p', 'q'], [prop_1, prop_2])
    equivalenceList = equivalenceTable.table

    equivalent = 1

    for row in equivalenceList:
        last_element = row[-1]
        if last_element[0] != last_element[1]:
            equivalent = 0

    if equivalent == 1:
        print ("The propositions are equivalent.")
    else:
        print("The propositions are not equivalent.")

if __name__ == "__main__":
    main()
