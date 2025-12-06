import sqlite3
from sqlite3 import Error
import math

"""
Executes a series of SQL queries and view creations on a TPC-H database.

This script interacts with a SQLite database ("tpch.sqlite") to create various views
aggregating customer, supplier, and order data, and then executes specific analytical
queries (Q1-Q15), saving the results to output files.
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


def create_View1(_conn):
    """
    Creates View V1 combining customer, nation, and region data.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Create V1")
    _conn.cursor().execute('DROP VIEW IF EXISTS V1;')
    _conn.commit()
    _conn.cursor().execute('''
        CREATE VIEW IF NOT EXISTS V1(
            c_custkey,
            c_name,
            c_address,
            c_phone,
            c_acctbal,
            c_mktsegment,
            c_comment,
            c_nation,
            c_region
        ) AS
        SELECT c_custkey,
            c_name,
            c_address,
            c_phone,
            c_acctbal,
            c_mktsegment,
            c_comment,
            n_name,
            r_name
        FROM customer,
            nation,
            region
        WHERE c_nationkey = n_nationkey
            AND n_regionkey = r_regionkey;
    ''')
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def create_View2(_conn):
    """
    Creates View V2 combining supplier, nation, and region data.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Create V2")

    _conn.cursor().execute('DROP VIEW IF EXISTS V2;')
    _conn.commit()
    _conn.cursor().execute('''
        CREATE VIEW IF NOT EXISTS V2(
            s_suppkey,
            s_name,
            s_address,
            s_phone,
            s_acctbal,
            s_comment,
            s_nation,
            s_region
        ) AS
        SELECT s_suppkey,
            s_name,
            s_address,
            s_phone,
            s_acctbal,
            s_comment,
            n_name,
            r_name
        FROM supplier,
            nation,
            region
        WHERE s_nationkey = n_nationkey
            AND n_regionkey = r_regionkey;
    ''')
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def create_View5(_conn):
    """
    Creates View V5 containing orders data with a formatted year.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Create V5")

    _conn.cursor().execute('DROP VIEW IF EXISTS V5;')
    _conn.commit()
    _conn.cursor().execute('''
        CREATE VIEW IF NOT EXISTS V5(
            o_orderkey,
            o_custkey,
            o_orderstatus,
            o_totalprice,
            o_orderyear,
            o_orderpriority,
            o_clerk,
            o_shippriority,
            o_comment
        ) AS
        SELECT o_orderkey,
            o_custkey,
            o_orderstatus,
            o_totalprice,
            substr(o_orderdate, 0, 5),
            o_orderpriority,
            o_clerk,
            o_shippriority,
            o_comment
        FROM orders;
    ''')
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def create_View10(_conn):
    """
    Creates View V10 aggregating max and min discounts by part type.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Create V10")

    _conn.cursor().execute('DROP VIEW IF EXISTS V10;')
    _conn.commit()
    _conn.cursor().execute('''
        CREATE VIEW IF NOT EXISTS V10(p_type, min_discount, max_discount) AS
        SELECT p_type,
            max(l_discount),
            min(l_discount)
        FROM part,
            lineitem
        WHERE p_partkey = l_partkey
        GROUP BY p_type;
    ''')
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def create_View151(_conn):
    """
    Creates View V151 for customers with positive account balances.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Create V151")

    _conn.cursor().execute('drop view if exists v151;')
    _conn.commit()
    _conn.cursor().execute('''
        CREATE VIEW IF NOT EXISTS V151(c_custkey, c_name, c_nationkey, c_acctbal) AS
        SELECT c_custkey,
            c_name,
            c_nationkey,
            c_acctbal
        FROM customer
        WHERE c_acctbal > 0;
    ''')
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def create_View152(_conn):
    """
    Creates View V152 for suppliers with negative account balances.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Create V152")

    _conn.cursor().execute('DROP VIEW IF EXISTS V152;')
    _conn.commit()
    _conn.cursor().execute('''
        CREATE VIEW IF NOT EXISTS V152(s_suppkey, s_name, s_nationkey, s_acctbal) AS
        SELECT s_suppkey,
            s_name,
            s_nationkey,
            s_acctbal
        FROM supplier
        WHERE s_acctbal < 0;
    ''')
    _conn.commit()

    print("++++++++++++++++++++++++++++++++++")


def Q1(_conn):
    """
    Executes Query 1: Total price by customer in France in 1995.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q1")
    with open('output/1.out', 'w') as outfile:
        for row in _conn.cursor().execute('select c_name, sum(o_totalprice) from orders, v1 where o_custkey = c_custkey and c_nation = \'FRANCE\' and o_orderdate like \'1995-__-__\' group by c_name;'):
            print(row)
            outfile.write('{}|{}\n'.format(row[0], round(row[1], 2)))
        _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q2(_conn):
    """
    Executes Query 2: Count of suppliers by region.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q2")

    with open('output/2.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT s_region,
            COUNT(*)
        FROM v2
        GROUP BY s_region;
        '''):
            print(row)
            outfile.write('{}|{}\n'.format(row[0], round(row[1], 2)))
            _conn.commit()
        outfile.close()

    print("++++++++++++++++++++++++++++++++++")


def Q3(_conn):
    """
    Executes Query 3: Count of orders by nation in America.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q3")
    with open('output/3.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT c_nation,
            COUNT(*)
        FROM orders,
            V1
        WHERE c_custkey = o_custkey
            AND c_region = 'AMERICA'
        GROUP BY c_nation;
        '''):
            print(row)
            outfile.write('{}|{}\n'.format(row[0], round(row[1], 2)))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q4(_conn):
    """
    Executes Query 4: Count of small parts supplied by Canadian suppliers.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q4")
    with open('output/4.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT s_name,
            COUNT(ps_partkey)
        FROM v2,
            partsupp,
            part
        WHERE p_partkey = ps_partkey
            AND ps_suppkey = s_suppkey
            AND s_nation = 'CANADA'
            AND p_size < 20
        GROUP BY s_name;
        '''):
            print(row)
            outfile.write('{}|{}\n'.format(row[0], round(row[1], 2)))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q5(_conn):
    """
    Executes Query 5: Count of orders by German customers in 1993.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q5")
    with open('output/5.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT c_name,
            COUNT(*)
        FROM v1,
            v5
        WHERE o_custkey = c_custkey
            AND c_nation = 'GERMANY'
            AND o_orderyear = '1993'
        GROUP BY c_name;
        '''):
            print(row)
            outfile.write('{}|{}\n'.format(row[0], round(row[1], 2)))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q6(_conn):
    """
    Executes Query 6: Count of distinct parts by Canadian suppliers and order priority.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q6")
    with open('output/6.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT s_name,
            o_orderpriority,
            COUNT(DISTINCT ps_partkey)
        FROM partsupp,
            V5,
            lineitem,
            supplier,
            nation
        WHERE l_orderkey = o_orderkey
            AND l_partkey = ps_partkey
            AND l_suppkey = ps_suppkey
            AND ps_suppkey = s_suppkey
            AND s_nationkey = n_nationkey
            AND n_name = 'CANADA'
        GROUP BY s_name,
            o_orderpriority;
        '''):
            print(row)
            outfile.write('{}|{}|{}\n'.format(row[0], row[1], row[2]))
            _conn.commit()
        outfile.close()

    print("++++++++++++++++++++++++++++++++++")


def Q7(_conn):
    """
    Executes Query 7: Count of orders by nation in America and order status.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q7")
    with open('output/7.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT c_nation,
            o_orderstatus,
            COUNT(*)
        FROM V5,
            V1
        WHERE o_custkey = c_custkey
            AND c_region = 'AMERICA'
        GROUP BY c_nation,
            o_orderstatus;
        '''):
            print(row)
            outfile.write('{}|{}|{}\n'.format(row[0], row[1], row[2]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q8(_conn):
    """
    Executes Query 8: Suppliers with more than 50 orders in 1995 with status 'F'.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q8")
    with open('output/8.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT s_nation,
            COUNT(DISTINCT l_orderkey) AS co
        FROM V5,
            nation,
            V2,
            lineitem
        WHERE o_orderkey = l_orderkey
            AND l_suppkey = s_suppkey
            AND s_nation = n_name
            AND o_orderstatus = 'F'
            AND o_orderyear = '1995'
        GROUP BY s_nation
        HAVING co > 50;
        '''):
            print(row)
            outfile.write('{}|{}\n'.format(row[0], row[1]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q9(_conn):
    """
    Executes Query 9: Count of distinct clerks handling orders from US suppliers.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q9")
    with open('output/9.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT COUNT(DISTINCT o_clerk)
        FROM V5,
            V2,
            lineitem
        WHERE o_orderkey = l_orderkey
            AND l_suppkey = s_suppkey
            AND s_nation = 'UNITED STATES';
        '''):
            print(row)
            outfile.write('{}\n'.format(row[0]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q10(_conn):
    """
    Executes Query 10: Discount range for 'ECONOMY' and 'COPPER' parts.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q10")
    with open('output/10.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT part.p_type,
            max_discount,
            min_discount
        FROM lineitem,
            part,
            V10
        WHERE l_partkey = p_partkey
            AND part.p_type LIKE '%ECONOMY%'
            AND part.p_type LIKE '%COPPER%'
        GROUP BY part.p_type;
        '''):
            print(row)
            outfile.write('{}|{}|{}\n'.format(row[0], row[1], row[2]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q11(_conn):
    """
    Executes Query 11: Maximum supplier account balance by region.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q11")
    with open('output/11.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT s_region,
            s_name,
            max(s_acctbal)
        FROM v2
        GROUP BY s_region
        '''):
            print(row)
            outfile.write('{}|{}|{}\n'.format(row[0], row[1], row[2]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q12(_conn):
    """
    Executes Query 12: Nations where max supplier account balance exceeds 9000.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q12")
    with open('output/12.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT s_nation,
            max(s_acctbal) AS mb
        FROM v2
        GROUP BY s_nation
        HAVING mb > 9000;
        '''):
            print(row)
            outfile.write('{}|{}\n'.format(row[0], row[1]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q13(_conn):
    """
    Executes Query 13: Count of lineitems linking African suppliers and US customers.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q13")
    with open('output/13.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT COUNT(*)
        FROM v2,
            v1,
            lineitem,
            orders
        WHERE s_region = 'AFRICA'
            AND c_nation = 'UNITED STATES'
            AND l_suppkey = s_suppkey
            AND l_orderkey = o_orderkey
            AND o_custkey = c_custkey
        '''):
            print(row)
            outfile.write('{}\n'.format(row[0]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q14(_conn):
    """
    Executes Query 14: Max order total price by supplier and customer regions.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q14")
    with open('output/14.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT s_region,
            c_region,
            max(o_totalprice)
        FROM v5,
            v2,
            v1,
            lineitem
        WHERE c_custkey = o_custkey
            AND o_orderkey = l_orderkey
            AND l_suppkey = s_suppkey
        GROUP BY s_region,
            c_region
        '''):
            print(row)
            outfile.write('{}|{}|{}\n'.format(row[0], row[1], row[2]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def Q15(_conn):
    """
    Executes Query 15: Count of distinct orders involving positive balance customers and negative balance suppliers.

    Args:
        _conn (sqlite3.Connection): The database connection object.
    """
    print("++++++++++++++++++++++++++++++++++")
    print("Q15")
    with open('output/15.out', 'w') as outfile:
        for row in _conn.cursor().execute('''
        SELECT COUNT(DISTINCT l_orderkey)
        FROM lineitem,
            V152,
            V151,
            orders
        WHERE c_custkey = o_custkey
            AND o_orderkey = l_orderkey
            AND l_suppkey = s_suppkey
        '''):
            print(row)
            outfile.write('{}\n'.format(row[0]))
            _conn.commit()
        outfile.close()
    print("++++++++++++++++++++++++++++++++++")


def main():
    """
    Main function to orchestrate the database operations and query execution.
    """
    database = r"tpch.sqlite"

    # create a database connection
    conn = openConnection(database)
    with conn:
        create_View1(conn)
        Q1(conn)

        create_View2(conn)
        Q2(conn)

        Q3(conn)
        Q4(conn)

        create_View5(conn)
        Q5(conn)

        Q6(conn)
        Q7(conn)
        Q8(conn)
        Q9(conn)

        create_View10(conn)
        Q10(conn)

        Q11(conn)
        Q12(conn)
        Q13(conn)
        Q14(conn)

        create_View151(conn)
        create_View152(conn)
        Q15(conn)

    closeConnection(conn, database)


if __name__ == '__main__':
    main()
