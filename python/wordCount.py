"""
Counts the occurrences of a specified word in a text file.

This script prompts the user for a word, reads the content of "PythonSummary.txt",
and counts how many times the specified word appears (case-insensitive).
"""

def main():
    """
    Main function to execute the word counting logic.
    """
    with open("PythonSummary.txt", "r") as file:
        search = input("Enter word to search for: ")
        count = 0
        for word in file.read().split(' '):
            if search.lower() in word.lower():
                count += 1
        print(count)

if __name__ == "__main__":
    main()
