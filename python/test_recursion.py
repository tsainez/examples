import unittest
import io
import sys
import os
from unittest.mock import patch

sys.path.insert(0, os.path.dirname(__file__))
from recursion import fib

class TestFibonacci(unittest.TestCase):
    @patch('sys.stdout', new_callable=io.StringIO)
    def test_fib_negative(self, mock_stdout):
        """Test that fib with a negative number prints 'Incorrect input' and returns None."""
        result = fib(-1)
        self.assertIsNone(result)
        self.assertEqual(mock_stdout.getvalue().strip(), "Incorrect input")

if __name__ == '__main__':
    unittest.main()
