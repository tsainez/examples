# adder.py
# Anthony Sainez

"""
A simple script to sum a list of numbers entered by the user.

The user is prompted to enter space-separated numbers. The script calculates
and prints the total sum. It handles invalid input by prompting the user again.
"""

def main():
    """
    Main function to run the adding logic.
    """
    while True:
        try:
            nums = input("Enter numbers: ")
            total = 0
            if(len(nums.split(' ')) > 1):
                for num in nums.split(' '):
                    total += float(num)
            print(total)
            break
        except ValueError:
            print("Error: incorrect input. Please try again.")
            continue

if __name__ == "__main__":
    main()
