"""
Tests for the recursive algorithms in python/recursion.py.
"""

import unittest
from unittest.mock import patch
import io
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from recursion import factorial, fib, addup

class TestRecursion(unittest.TestCase):
    """
    Test suite for the recursive functions in recursion.py.
    """

    def test_fib_negative(self):
        """
        Test that fib handles negative inputs by printing 'Incorrect input' and returning None.
        """
        with patch('sys.stdout', new_callable=io.StringIO) as mock_stdout:
            result = fib(-1)
            self.assertIsNone(result)
            self.assertEqual(mock_stdout.getvalue().strip(), "Incorrect input")

    def test_fib_base_cases(self):
        """
        Test the base cases for the fibonacci sequence.
        """
        self.assertEqual(fib(1), 0)
        self.assertEqual(fib(2), 1)

    def test_fib_positive(self):
        """
        Test the recursive case for a known positive index.
        """
        self.assertEqual(fib(8), 13)

    def test_fib_zero_raises_typeerror(self):
        """
        Test that fib(0) raises a TypeError due to None + None.
        """
        with patch('sys.stdout', new_callable=io.StringIO):
            with self.assertRaises(TypeError):
                fib(0)

if __name__ == '__main__':
    unittest.main()
