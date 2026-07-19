import unittest
import sys
import os

# Add the root directory to the python path so we can import the module correctly
sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
from python.truth_table_generator import generate

class TestTruthTableGenerator(unittest.TestCase):

    def test_generate_1_variable(self):
        """Test generating truth table values for 1 variable."""
        result = generate(['p'])
        self.assertEqual(len(result), 2)  # 2^1 rows
        self.assertTrue(all(len(row) == 1 for row in result))  # 1 column
        self.assertEqual(result, [[0], [1]])

    def test_generate_2_variables(self):
        """Test generating truth table values for 2 variables."""
        result = generate(['p', 'q'])
        self.assertEqual(len(result), 4)  # 2^2 rows
        self.assertTrue(all(len(row) == 2 for row in result))  # 2 columns
        self.assertEqual(result, [[0, 0], [0, 1], [1, 0], [1, 1]])

    def test_generate_3_variables(self):
        """Test generating truth table values for 3 variables."""
        result = generate(['p', 'q', 'r'])
        self.assertEqual(len(result), 8)  # 2^3 rows
        self.assertTrue(all(len(row) == 3 for row in result))  # 3 columns
        self.assertEqual(result, [
            [0, 0, 0],
            [0, 0, 1],
            [0, 1, 0],
            [0, 1, 1],
            [1, 0, 0],
            [1, 0, 1],
            [1, 1, 0],
            [1, 1, 1]
        ])

    def test_generate_empty_variables(self):
        """Test generating truth table values with an empty variable list."""
        result = generate([])
        self.assertEqual(result, [[]])

if __name__ == '__main__':
    unittest.main()
