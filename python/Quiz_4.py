import sqlite3
from sqlite3 import Error


def openConnection(_dbFile):
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
    print("++++++++++++++++++++++++++++++++++")
    print("Close database: ", _dbFile)

    try:
        _conn.close()
        print("success")
    except Error as e:
        print(e)

    print("++++++++++++++++++++++++++++++++++")


def createPriceRange(_conn):
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
    print("++++++++++++++++++++++++++++++++++")
    l = 'Update Printer ({}, {})'.format(_model, _price)
    print(l)
    cursor = _conn.cursor()
    cursor.exucte(
        'UPDATE printer SET price = {} WHERE model = {};'.format(_price, _model))
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def deleteLaptop(_conn, _model):
    print("++++++++++++++++++++++++++++++++++")
    l = 'Delete Laptop ({})'.format(_model)
    print(l)

    cursor = _conn.cursor()
    cursor.execute('DELETE FROM laptop WHERE model = {}'.format(_model))
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def main():
    database = "data.sqlite"

    # create a database connection
    conn = openConnection(database)
    with conn:
        createPriceRange(conn)
        printPriceRange(conn)

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

    closeConnection(conn, database)


if __name__ == '__main__':
    main()
