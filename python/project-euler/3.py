"""
Solves Project Euler Problem #3.

Problem Statement:
The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143 ?
"""

def largest_prime_factor(n):
    """
    Finds the largest prime factor of a given number.

    Args:
        n (int): The number to find the largest prime factor of.

    Returns:
        int: The largest prime factor of n.
    """
    i = 2
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
    return n

def main():
    """
    Main function to solve Project Euler Problem #3.
    """
    print(largest_prime_factor(600851475143))

if __name__ == "__main__":
    main()
