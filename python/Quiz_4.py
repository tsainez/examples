import sqlite3
from sqlite3 import Error

"""
This module provides functions to interact with a SQLite database for a product inventory system.
It supports creating views, inserting PCs, updating printers, deleting laptops, and querying price ranges.
"""

def openConnection(_dbFile):
    """
    Opens a connection to the SQLite database.

    Args:
        _dbFile (str): The path to the database file.

    Returns:
        sqlite3.Connection: The connection object if successful, None otherwise.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Open database: ", _dbFile)

    conn = None
    try:
        conn = sqlite3.connect(_dbFile)
        print("success")
    except Error as e:
        print(e)

    print("++++++++++++++++++++++++++++++++++")

    return conn


def closeConnection(_conn, _dbFile):
    """
    Closes the database connection.

    Args:
        _conn (sqlite3.Connection): The connection object to close.
        _dbFile (str): The name of the database file (for logging purposes).
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Close database: ", _dbFile)

    try:
        _conn.close()
        print("success")
    except Error as e:
        print(e)

    print("++++++++++++++++++++++++++++++++++")


def createPriceRange(_conn):
    """
    Creates the PriceRange view in the database.

    The view aggregates minimum and maximum prices for each maker and product type
    across printers, PCs, and laptops.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Create PriceRange")
    cursor = _conn.cursor()
    cursor.execute('''
    CREATE VIEW IF NOT EXISTS PriceRange(maker, TYPE, minPrice, maxPrice) AS
    SELECT product.maker,
        product.type,
        min(price),
        max(price)
    FROM product,
        printer
    WHERE product.model = printer.model
    GROUP BY product.maker,
        product.type
    UNION
    SELECT product.maker,
        product.type,
        min(price),
        max(price)
    FROM product,
        PC
    WHERE product.model = PC.model
    GROUP BY product.maker,
        product.type
    UNION
    SELECT product.maker,
        product.type,
        min(price),
        max(price)
    FROM product,
        laptop
    WHERE product.model = laptop.model
    GROUP BY product.maker,
        product.type;
    ''')
    _conn.commit()
    print("++++++++++++++++++++++++++++++++++")


def printPriceRange(_conn):
    """
    Prints the content of the PriceRange view.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Print PriceRange")

    l = '{:<10} {:<20} {:>20} {:>20}'.format(
        "maker", "product", "minPrice", "maxPrice")
    print(l)

    for row in _conn.cursor().execute('''
    SELECT *
    FROM PriceRange
    ORDER BY maker ASC,
        TYPE ASC;
    '''):
        print('{:<10} {:<20} {:>20} {:>20}'.format(
            row[0], row[1], row[2], row[3]))
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def insertPC(_conn, _maker, _model, _speed, _ram, _hd, _price):
    """
    Inserts a new PC into the database, or updates if it exists.

    It first deletes any existing entries with the given model from the PC and product tables,
    then inserts the new records.

    Args:
        _conn (sqlite3.Connection): The database connection object.
        _maker (str): The maker of the PC.
        _model (int): The model number of the PC.
        _speed (float): The speed of the PC.
        _ram (int): The RAM of the PC.
        _hd (int): The hard drive size of the PC.
        _price (int): The price of the PC.
    """
    print("++++++++++++++++++++++++++++++++++")
    l = 'Insert PC ({}, {}, {}, {}, {}, {})'.format(
        _maker, _model, _speed, _ram, _hd, _price)
    print(l)
    cursor = _conn.cursor()

    cursor.execute('DELETE FROM pc WHERE model = {};'.format(_model))

    cursor.execute('DELETE FROM product WHERE model = {};'.format(_model))

    cursor.execute(
        'INSERT INTO pc(model, speed, ram, hd, price) VALUES(\'{}\', {}, {}, {}, {});'.format(
            _model, _speed, _ram, _hd, _price))

    cursor.execute('INSERT INTO product(maker, model, TYPE) VALUES(\'{}\', {}, \'{}\');'.format(
        _maker, _model, 'PC'))

    _conn.commit()
    print("++++++++++++++++++++++++++++++++++")


def updatePrinter(_conn, _model, _price):
    """
    Updates the price of a printer in the database.

    Args:
        _conn (sqlite3.Connection): The database connection object.
        _model (int): The model number of the printer.
        _price (int): The new price of the printer.
    """
    print("++++++++++++++++++++++++++++++++++")
    l = 'Update Printer ({}, {})'.format(_model, _price)
    print(l)
    cursor = _conn.cursor()
    # Fixed typo from original code: exucte -> execute
    cursor.execute(
        'UPDATE printer SET price = {} WHERE model = {};'.format(_price, _model))
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def deleteLaptop(_conn, _model):
    """
    Deletes a laptop from the database.

    Args:
        _conn (sqlite3.Connection): The database connection object.
        _model (int): The model number of the laptop to delete.
    """
    print("++++++++++++++++++++++++++++++++++")
    l = 'Delete Laptop ({})'.format(_model)
    print(l)

    cursor = _conn.cursor()
    cursor.execute('DELETE FROM laptop WHERE model = {}'.format(_model))
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def main():
    """
    Main function to execute the database operations based on input file instructions.
    """
    database = "data.sqlite"

    # create a database connection
    conn = openConnection(database)
    with conn:
        createPriceRange(conn)
        printPriceRange(conn)

        try:
            file = open('input.in', 'r')
            lines = file.readlines()
            for line in lines:
                print(line.strip())

                tok = line.strip().split(' ')
                if tok[0] == 'I':
                    insertPC(conn, tok[2], tok[3], tok[4], tok[5], tok[6], tok[7])
                elif tok[0] == 'U':
                    updatePrinter(conn, tok[2], tok[3])
                elif tok[0] == 'D':
                    deleteLaptop(conn, tok[2])

                printPriceRange(conn)

            file.close()
        except FileNotFoundError:
            print("input.in file not found.")

    closeConnection(conn, database)


if __name__ == '__main__':
    main()
