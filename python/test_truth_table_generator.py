import unittest
from truth_table_generator import liff

class TestTruthTableGenerator(unittest.TestCase):
    def test_liff(self):
        # Boolean inputs
        self.assertTrue(liff(True, True))
        self.assertFalse(liff(True, False))
        self.assertFalse(liff(False, True))
        self.assertTrue(liff(False, False))

        # Integer inputs (0 and 1 are common for truth tables)
        self.assertTrue(liff(1, 1))
        self.assertFalse(liff(1, 0))
        self.assertFalse(liff(0, 1))
        self.assertTrue(liff(0, 0))

if __name__ == '__main__':
    unittest.main()
