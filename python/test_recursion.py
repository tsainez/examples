import unittest
from recursion import addup

class TestAddup(unittest.TestCase):
    def test_empty_list(self):
        self.assertEqual(addup([]), 0)

    def test_single_element(self):
        self.assertEqual(addup([5]), 5)

    def test_positive_integers(self):
        self.assertEqual(addup([1, 2, 3, 4, 5]), 15)

    def test_negative_integers(self):
        self.assertEqual(addup([-1, -2, -3, -4]), -10)

    def test_mixed_integers(self):
        self.assertEqual(addup([-1, 2, -3, 4, 0]), 2)

    def test_floats(self):
        self.assertEqual(addup([1.5, 2.5, 3.5]), 7.5)

    def test_range(self):
        self.assertEqual(addup(range(101)), 5050)

if __name__ == '__main__':
    unittest.main()
