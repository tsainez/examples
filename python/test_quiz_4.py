import unittest
import sqlite3
from Quiz_4 import insertPC, updatePrinter, deleteLaptop

class TestQuiz4(unittest.TestCase):
    def setUp(self):
        # Create an in-memory SQLite database
        self.conn = sqlite3.connect(':memory:')
        self.cursor = self.conn.cursor()

        # Create required tables for testing
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS product (
                maker VARCHAR(10),
                model INT PRIMARY KEY,
                TYPE VARCHAR(20)
            )
        ''')
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS pc (
                model INT PRIMARY KEY,
                speed FLOAT,
                ram INT,
                hd INT,
                price INT
            )
        ''')
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS printer (
                model INT PRIMARY KEY,
                price INT
            )
        ''')
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS laptop (
                model INT PRIMARY KEY,
                speed FLOAT,
                ram INT,
                hd INT,
                price INT
            )
        ''')

        # Insert some initial data
        self.cursor.execute("INSERT INTO product(maker, model, TYPE) VALUES('A', 1001, 'PC')")
        self.cursor.execute("INSERT INTO pc(model, speed, ram, hd, price) VALUES(1001, 2.66, 1024, 250, 2114)")

        self.cursor.execute("INSERT INTO printer(model, price) VALUES(3001, 120)")

        self.cursor.execute("INSERT INTO laptop(model, speed, ram, hd, price) VALUES(2001, 2.00, 2048, 250, 3150)")
        self.conn.commit()

    def tearDown(self):
        self.conn.close()

    def test_insertPC(self):
        # Test inserting a new PC
        insertPC(self.conn, 'B', 1002, 3.0, 2048, 500, 1000)

        self.cursor.execute("SELECT * FROM pc WHERE model = 1002")
        result = self.cursor.fetchone()
        self.assertIsNotNone(result)
        self.assertEqual(result, (1002, 3.0, 2048, 500, 1000))

        self.cursor.execute("SELECT * FROM product WHERE model = 1002")
        result = self.cursor.fetchone()
        self.assertIsNotNone(result)
        self.assertEqual(result, ('B', 1002, 'PC'))

        # Test updating (replacing) an existing PC
        insertPC(self.conn, 'B', 1002, 3.2, 4096, 1000, 1500)
        self.cursor.execute("SELECT * FROM pc WHERE model = 1002")
        result = self.cursor.fetchone()
        self.assertIsNotNone(result)
        self.assertEqual(result, (1002, 3.2, 4096, 1000, 1500))

        # Test preventing SQL injection in insertPC (e.g. maker with quotes)
        # Assuming maker name "Inject'; DROP TABLE pc; --"
        malicious_maker = "Inject'; DROP TABLE pc; --"
        insertPC(self.conn, malicious_maker, 1003, 2.0, 1024, 250, 500)

        # Verify table pc still exists by fetching
        self.cursor.execute("SELECT * FROM pc WHERE model = 1003")
        result = self.cursor.fetchone()
        self.assertIsNotNone(result)

        self.cursor.execute("SELECT maker FROM product WHERE model = 1003")
        maker_result = self.cursor.fetchone()
        self.assertEqual(maker_result[0], malicious_maker)

    def test_updatePrinter(self):
        # Test updating an existing printer
        updatePrinter(self.conn, 3001, 150)
        self.cursor.execute("SELECT price FROM printer WHERE model = 3001")
        result = self.cursor.fetchone()
        self.assertEqual(result[0], 150)

    def test_deleteLaptop(self):
        # Test deleting an existing laptop
        deleteLaptop(self.conn, 2001)
        self.cursor.execute("SELECT * FROM laptop WHERE model = 2001")
        result = self.cursor.fetchone()
        self.assertIsNone(result)

        # Test preventing SQL injection in deleteLaptop
        self.cursor.execute("INSERT INTO laptop(model, speed, ram, hd, price) VALUES(2002, 2.00, 2048, 250, 3150)")
        self.conn.commit()

        # Attempt injection to delete all or something
        malicious_model = "2002 OR 1=1"
        deleteLaptop(self.conn, malicious_model)

        # If parameterized properly, it shouldn't execute the injection. It will either fail to match or delete literally that string if somehow model allows string (which here it's INT but SQLite is flexible).
        # We can check if 2002 still exists
        self.cursor.execute("SELECT * FROM laptop WHERE model = 2002")
        result = self.cursor.fetchone()
        self.assertIsNotNone(result)

if __name__ == '__main__':
    unittest.main()
