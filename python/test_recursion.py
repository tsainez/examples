import unittest
from io import StringIO
from unittest.mock import patch
import recursion

class TestRecursion(unittest.TestCase):

    def test_factorial(self):
        self.assertEqual(recursion.factorial(0), 1)
        self.assertEqual(recursion.factorial(1), 1)
        self.assertEqual(recursion.factorial(5), 120)
        self.assertEqual(recursion.factorial(10), 3628800)

    def test_fib(self):
        # fib(1) -> 0
        # fib(2) -> 1
        # fib(3) -> 1
        # fib(4) -> 2
        # fib(5) -> 3
        # fib(6) -> 5
        # fib(7) -> 8
        # fib(8) -> 13
        self.assertEqual(recursion.fib(1), 0)
        self.assertEqual(recursion.fib(2), 1)
        self.assertEqual(recursion.fib(8), 13)

        # Test negative input
        with patch('sys.stdout', new=StringIO()) as fake_out:
            recursion.fib(-1)
            output = fake_out.getvalue().strip()
            self.assertEqual(output, "Incorrect input")

    def test_addup(self):
        self.assertEqual(recursion.addup([]), 0)
        self.assertEqual(recursion.addup([1]), 1)
        self.assertEqual(recursion.addup([1, 2, 3]), 6)
        self.assertEqual(recursion.addup(range(101)), 5050)

if __name__ == '__main__':
    unittest.main()
