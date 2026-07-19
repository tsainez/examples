import unittest
from recursion import factorial

class TestFactorial(unittest.TestCase):
    def test_factorial_base_case(self):
        """Test factorial with n=0."""
        self.assertEqual(factorial(0), 1)

    def test_factorial_positive_integers(self):
        """Test factorial with positive integers."""
        self.assertEqual(factorial(1), 1)
        self.assertEqual(factorial(2), 2)
        self.assertEqual(factorial(3), 6)
        self.assertEqual(factorial(4), 24)
        self.assertEqual(factorial(5), 120)
        self.assertEqual(factorial(10), 3628800)

    def test_factorial_negative_integer(self):
        """Test factorial with a negative integer, which should cause infinite recursion (RecursionError)."""
        import sys
        original_limit = sys.getrecursionlimit()
        sys.setrecursionlimit(100) # Lower limit to avoid segfaults
        try:
            with self.assertRaises(RecursionError):
                factorial(-1)
        finally:
            sys.setrecursionlimit(original_limit)

if __name__ == '__main__':
    unittest.main()
