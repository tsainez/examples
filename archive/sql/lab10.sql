-- Create a trigger t1 that for every new order entry automatically fills 
-- the o_orderdate attribute with the date 2021-12-01.  Insert into orders 
-- all the orders from December 1996, paying close attention on how the 
-- o_orderkey attribute is set.  Write a query that returns the number of 
-- orders from 2021. Put all the three SQL statements in filetest/1.sql.
DROP TRIGGER IF EXISTS t1;
--
CREATE TRIGGER t1
AFTER
INSERT ON orders BEGIN
UPDATE orders
SET o_orderdate = '2021-12-01'
WHERE o_orderkey = NEW.o_orderkey;
END;
--
INSERT INTO orders
SELECT orders.o_orderkey + sub_query.max_id,
    o_custkey,
    o_orderstatus,
    o_totalprice,
    o_orderdate,
    o_orderpriority,
    o_clerk,
    o_shippriority,
    o_comment
FROM orders,
    (
        SELECT max(o_orderkey) AS max_id
        FROM orders
    ) AS sub_query
WHERE substr(o_orderdate, 0, 8) BETWEEN '1996-12' AND '1996-12';
--
SELECT COUNT(*)
FROM orders
WHERE o_orderdate LIKE '%2021%';
--
-- Create a trigger t2 that sets a warning Negative balance!!! in the comment
-- attribute of the customer table every time c_acctbal is updated to a 
-- negative value from a positive one. Write a SQL statement that sets the 
-- balance to -100 for all the customers in AMERICA. Write a query that returns
-- the number of customers with negative balance from CANADA. Put all the SQL
-- statements in file test/2.sql.
DROP TRIGGER IF EXISTS t2;
--
CREATE TRIGGER t2
AFTER
UPDATE ON customer FOR each ROW
    WHEN (
        new.c_acctbal < 0
        AND old.c_acctbal > 0
    ) BEGIN
UPDATE customer
SET c_comment = 'Negative balance!!!'
WHERE c_custkey = new.c_custkey;
END;
--
UPDATE customer
SET c_acctbal = -100
WHERE c_nationkey IN (
        SELECT n_nationkey
        FROM nation,
            region
        WHERE n_regionkey = r_regionkey
            AND r_name = 'AMERICA'
    );
--
SELECT COUNT(*)
FROM customer,
    nation
WHERE c_nationkey = n_nationkey
    AND n_name = 'CANADA'
    AND c_acctbal < 0;
-- Create a trigger t3 that resets the comment to Positive balance if
-- the balance goes back positive from negative. Write a SQL statement
-- that sets the balance to 100 for all the customers in UNITEDSTATES.
-- Write a query that returns the number of customers with negative balance
-- from AMERICA. Put all the SQL statements in file test/3.sql.
DROP TRIGGER IF EXISTS t3;
--
CREATE TRIGGER t3
AFTER
UPDATE ON customer FOR each ROW
    WHEN (
        new.c_acctbal > 0
        AND old.c_acctbal < 0
    ) BEGIN
UPDATE customer
SET c_comment = 'Positive balance'
WHERE c_custkey = new.c_custkey;
END;
--
UPDATE customer
SET c_acctbal = 100
WHERE c_nationkey IN (
        SELECT n_nationkey
        FROM nation
        WHERE n_name = 'UNITED STATES'
    );
--
SELECT COUNT(c_custkey)
FROM customer,
    nation,
    region
WHERE c_acctbal < 0
    AND c_nationkey = n_nationkey
    AND n_regionkey = r_regionkey
    AND r_name = 'AMERICA';
-- Create triggers that update the attribute o_orderpriority 
-- to HIGH every time a new lineitem tuple is added to or deleted
-- from that order. Delete all the line items corresponding to 
-- orders from December 1995. Write a query that returns the number
-- of HIGH priority orders in the fourth trimester of 1995. Put all
-- the SQL statements in file test/4.sql.
DROP TRIGGER IF EXISTS t4_1;
-- 
CREATE TRIGGER t4_1
AFTER DELETE ON lineitem BEGIN
UPDATE orders
SET o_orderpriority = 'HIGH'
WHERE o_orderkey = old.l_orderkey;
END;
--
DROP TRIGGER IF EXISTS t4_2;
--
CREATE TRIGGER t4_2
AFTER
INSERT ON lineitem BEGIN
UPDATE orders
SET o_orderpriority = 'HIGH'
WHERE o_orderkey = old.l_orderkey;
END;
--
DELETE FROM lineitem
WHERE l_orderkey IN (
        SELECT o_orderkey
        FROM orders
        WHERE substr(o_orderdate, 0, 8) = '1995-12'
    );
--
SELECT COUNT(*)
FROM orders
WHERE o_orderpriority = 'HIGH'
    AND substr(o_orderdate, 0, 8) BETWEEN '1995-09' AND '1995-12';
--
-- Create a trigger t5 that removes all the tuples from partsupp and lineitem
-- corresponding to a part being deleted. Delete all the parts supplied by 
-- suppliers from UNITED STATES or CANADA. Write a query that returns the
-- number of parts supplied by every supplier in AMERICA grouped by their
-- country in increasing order. Put all the SQL statements in file test/5.sql
DROP TRIGGER IF EXISTS t5;
--
CREATE TRIGGER t5
AFTER DELETE ON part BEGIN
DELETE FROM lineitem
WHERE l_partkey = old.p_partkey;
DELETE FROM partsupp
WHERE ps_partkey = old.p_partkey;
END;
--
DELETE FROM part
WHERE p_partkey IN (
        SELECT p_partkey
        FROM part,
            partsupp,
            supplier,
            nation,
            region
        WHERE ps_partkey = p_partkey
            AND ps_suppkey = s_suppkey
            AND n_nationkey = s_nationkey
            AND n_regionkey = r_regionkey
            AND (
                n_name = 'UNITED STATES'
                OR n_name = 'CANADA'
            )
    );
--
SELECT n_name,
    COUNT(*)
FROM part,
    partsupp,
    supplier,
    nation,
    region
WHERE p_partkey = ps_partkey
    AND ps_suppkey = s_suppkey
    AND s_nationkey = n_nationkey
    AND n_regionkey = r_regionkey
    AND r_name = 'AMERICA'
GROUP BY n_name;
--