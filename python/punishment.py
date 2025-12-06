"""
Writes a user-defined sentence to a file multiple times.

This script prompts the user for a sentence and a repetition count, then writes
the sentence to "CompletedPunishment.txt" the specified number of times.
"""

def main():
    """
    Main function to execute the punishment writing logic.
    """
    with open("CompletedPunishment.txt", "w") as file:
        sentence = input("Enter in a sentence: ")
        repeats = input("Enter in how many times to repeat: ")
        for i in range(int(repeats)):
            file.write(sentence + "\n")

if __name__ == "__main__":
    main()
