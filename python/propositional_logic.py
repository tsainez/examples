from truth_table_generator import TruthTable

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

