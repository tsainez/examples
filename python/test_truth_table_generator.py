import unittest
from truth_table_generator import land

class TestTruthTableGenerator(unittest.TestCase):
    def test_land(self):
        # Boolean inputs
        self.assertTrue(land(True, True))
        self.assertFalse(land(True, False))
        self.assertFalse(land(False, True))
        self.assertFalse(land(False, False))

        # Integer inputs
        self.assertTrue(land(1, 1))
        self.assertFalse(land(1, 0))
        self.assertFalse(land(0, 1))
        self.assertFalse(land(0, 0))

if __name__ == '__main__':
    unittest.main()
