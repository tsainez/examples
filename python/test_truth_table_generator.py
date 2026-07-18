import unittest
from truth_table_generator import lif

class TestTruthTableGenerator(unittest.TestCase):

    def test_lif_boolean(self):
        # T -> T is T
        self.assertTrue(lif(True, True))
        # T -> F is F
        self.assertFalse(lif(True, False))
        # F -> T is T
        self.assertTrue(lif(False, True))
        # F -> F is T
        self.assertTrue(lif(False, False))

    def test_lif_integer(self):
        # 1 -> 1 is 1 (True equivalent)
        self.assertTrue(lif(1, 1))
        # 1 -> 0 is 0 (False equivalent)
        self.assertFalse(lif(1, 0))
        # 0 -> 1 is 1 (True equivalent)
        self.assertTrue(lif(0, 1))
        # 0 -> 0 is 1 (True equivalent)
        self.assertTrue(lif(0, 0))

if __name__ == '__main__':
    unittest.main()
