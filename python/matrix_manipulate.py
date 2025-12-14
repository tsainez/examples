"""
Performs various matrix operations using NumPy.

This script demonstrates matrix addition, cross product, determinant calculation,
inverse calculation, and eigenvalue computation.
"""

import numpy as np

def main():
    """
    Main function to execute the matrix manipulation demonstrations.
    """
    a = np.array([[1, 2, 3, ],
                  [4, 5, 6, ],
                  [7, 8, 9]])
    b = np.array([[3, 1, 4, ],
                  [2, 6, 1],
                  [2, 9, 7]])

    print("-------------------- Part A --------------------")
    # Matrix Addition
    print(a + b)

    print("-------------------- Part B --------------------")
    # Cross Product (row-wise)
    print(np.cross(a, b))

    print("-------------------- Part C --------------------")
    # Determinant of matrix 'a'
    print(np.linalg.det(a))

    print("-------------------- Part D --------------------")
    # Inverse of matrix 'b'
    print(np.linalg.inv(b))

    print("-------------------- Part E --------------------")
    # Eigenvalues of matrix 'a'
    print(np.linalg.eigvals(a))

if __name__ == "__main__":
    main()
