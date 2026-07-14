import unittest
import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from truth_table_generator import lnot

class TestTruthTableGenerator(unittest.TestCase):
    def test_lnot(self):
        """Test the logical NOT function."""
        # Test boolean values
        self.assertFalse(lnot(True))
        self.assertTrue(lnot(False))

        # Test integer values commonly used as booleans
        self.assertFalse(lnot(1))
        self.assertTrue(lnot(0))

if __name__ == '__main__':
    unittest.main()
