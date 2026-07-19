import unittest
import sqlite3
import os
from Quiz_4 import insertPC, updatePrinter, deleteLaptop, createPriceRange

class TestQuiz4SecurityFix(unittest.TestCase):
    def setUp(self):
        # Create an in-memory SQLite database
        self.conn = sqlite3.connect(':memory:')
        self.cursor = self.conn.cursor()

        # Create tables as expected by the script
        self.cursor.execute('''
            CREATE TABLE product (
                maker TEXT,
                model INTEGER PRIMARY KEY,
                type TEXT
            )
        ''')
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
            CREATE TABLE laptop (
                model INTEGER PRIMARY KEY,
                speed REAL,
                ram INTEGER,
                hd INTEGER,
                screen REAL,
                price INTEGER
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
        self.conn.commit()

    def tearDown(self):
        self.conn.close()

    def test_insertPC_parameterized(self):
        # Test that insertPC works correctly and doesn't suffer from string formatting issues
        maker = "MakerA"
        model = 1001
        speed = 3.2
        ram = 16
        hd = 500
        price = 1200

        insertPC(self.conn, maker, model, speed, ram, hd, price)

        self.cursor.execute("SELECT * FROM pc WHERE model=?", (model,))
        pc_record = self.cursor.fetchone()
        self.assertIsNotNone(pc_record)
        self.assertEqual(pc_record[0], model)
        self.assertEqual(pc_record[4], price)

        self.cursor.execute("SELECT * FROM product WHERE model=?", (model,))
        product_record = self.cursor.fetchone()
        self.assertIsNotNone(product_record)
        self.assertEqual(product_record[0], maker)

    def test_updatePrinter_parameterized(self):
        # Insert a printer to update
        model = 2001
        initial_price = 150
        self.cursor.execute("INSERT INTO printer (model, color, type, price) VALUES (?, 'true', 'laser', ?)", (model, initial_price))
        self.cursor.execute("INSERT INTO product (maker, model, type) VALUES ('MakerB', ?, 'printer')", (model,))
        self.conn.commit()

        new_price = 200
        updatePrinter(self.conn, model, new_price)

        self.cursor.execute("SELECT price FROM printer WHERE model=?", (model,))
        updated_price = self.cursor.fetchone()[0]
        self.assertEqual(updated_price, new_price)

    def test_deleteLaptop_parameterized(self):
        # Insert a laptop to delete
        model = 3001
        self.cursor.execute("INSERT INTO laptop (model, speed, ram, hd, screen, price) VALUES (?, 2.0, 8, 256, 15.6, 800)", (model,))
        self.cursor.execute("INSERT INTO product (maker, model, type) VALUES ('MakerC', ?, 'laptop')", (model,))
        self.conn.commit()

        # Verify it's there
        self.cursor.execute("SELECT * FROM laptop WHERE model=?", (model,))
        self.assertIsNotNone(self.cursor.fetchone())

        # Delete it
        deleteLaptop(self.conn, model)

        # Verify it's gone
        self.cursor.execute("SELECT * FROM laptop WHERE model=?", (model,))
        self.assertIsNone(self.cursor.fetchone())

if __name__ == '__main__':
    unittest.main()
