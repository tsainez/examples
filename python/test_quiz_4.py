import unittest
import sqlite3
from Quiz_4 import insertPC, updatePrinter, deleteLaptop

class TestQuiz4(unittest.TestCase):
    def setUp(self):
        # Create an in-memory database for testing
        self.conn = sqlite3.connect(':memory:')
        self.cursor = self.conn.cursor()

        # Create the necessary tables
        self.cursor.execute('''
            CREATE TABLE pc (
                model INTEGER PRIMARY KEY,
                speed REAL,
                ram INTEGER,
                hd INTEGER,
                price INTEGER
            )
        ''')

        self.cursor.execute('''
            CREATE TABLE product (
                maker TEXT,
                model INTEGER PRIMARY KEY,
                type TEXT
            )
        ''')

        self.cursor.execute('''
            CREATE TABLE printer (
                model INTEGER PRIMARY KEY,
                color TEXT,
                type TEXT,
                price INTEGER
            )
        ''')

        self.cursor.execute('''
            CREATE TABLE laptop (
                model INTEGER PRIMARY KEY,
                speed REAL,
                ram INTEGER,
                hd INTEGER,
                screen REAL,
                price INTEGER
            )
        ''')

        self.conn.commit()

    def tearDown(self):
        self.conn.close()

    def test_insertPC(self):
        # Test inserting a PC
        insertPC(self.conn, 'A', 1001, 2.66, 1024, 250, 2114)

        # Verify insertion into pc table
        self.cursor.execute('SELECT * FROM pc WHERE model = 1001')
        pc_result = self.cursor.fetchone()
        self.assertIsNotNone(pc_result)
        self.assertEqual(pc_result, (1001, 2.66, 1024, 250, 2114))

        # Verify insertion into product table
        self.cursor.execute('SELECT * FROM product WHERE model = 1001')
        product_result = self.cursor.fetchone()
        self.assertIsNotNone(product_result)
        self.assertEqual(product_result, ('A', 1001, 'PC'))

    def test_updatePrinter(self):
        # Insert a printer first
        self.cursor.execute("INSERT INTO printer (model, color, type, price) VALUES (3001, 'true', 'ink-jet', 99)")
        self.conn.commit()

        # Test updating the printer
        updatePrinter(self.conn, 3001, 150)

        # Verify update
        self.cursor.execute('SELECT price FROM printer WHERE model = 3001')
        price_result = self.cursor.fetchone()[0]
        self.assertEqual(price_result, 150)

    def test_deleteLaptop(self):
        # Insert a laptop first
        self.cursor.execute("INSERT INTO laptop (model, speed, ram, hd, screen, price) VALUES (2001, 2.0, 2048, 240, 20.1, 3150)")
        self.conn.commit()

        # Test deleting the laptop
        deleteLaptop(self.conn, 2001)

        # Verify deletion
        self.cursor.execute('SELECT * FROM laptop WHERE model = 2001')
        laptop_result = self.cursor.fetchone()
        self.assertIsNone(laptop_result)

if __name__ == '__main__':
    unittest.main()
