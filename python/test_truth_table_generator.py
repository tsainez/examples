import unittest
from truth_table_generator import lor, land, lnot, lif, liff

class TestTruthTableGenerator(unittest.TestCase):
    def test_lor(self):
        # Boolean inputs
        self.assertTrue(lor(True, True))
        self.assertTrue(lor(True, False))
        self.assertTrue(lor(False, True))
        self.assertFalse(lor(False, False))

        # Integer inputs
        self.assertTrue(lor(1, 1))
        self.assertTrue(lor(1, 0))
        self.assertTrue(lor(0, 1))
        self.assertFalse(lor(0, 0))

    def test_land(self):
        self.assertTrue(land(True, True))
        self.assertFalse(land(True, False))
        self.assertFalse(land(False, True))
        self.assertFalse(land(False, False))

        self.assertTrue(land(1, 1))
        self.assertFalse(land(1, 0))
        self.assertFalse(land(0, 1))
        self.assertFalse(land(0, 0))

    def test_lnot(self):
        self.assertFalse(lnot(True))
        self.assertTrue(lnot(False))

        self.assertFalse(lnot(1))
        self.assertTrue(lnot(0))

    def test_lif(self):
        self.assertTrue(lif(True, True))
        self.assertFalse(lif(True, False))
        self.assertTrue(lif(False, True))
        self.assertTrue(lif(False, False))

        self.assertTrue(lif(1, 1))
        self.assertFalse(lif(1, 0))
        self.assertTrue(lif(0, 1))
        self.assertTrue(lif(0, 0))

    def test_liff(self):
        self.assertTrue(liff(True, True))
        self.assertFalse(liff(True, False))
        self.assertFalse(liff(False, True))
        self.assertTrue(liff(False, False))

        self.assertTrue(liff(1, 1))
        self.assertFalse(liff(1, 0))
        self.assertFalse(liff(0, 1))
        self.assertTrue(liff(0, 0))

if __name__ == '__main__':
    unittest.main()
