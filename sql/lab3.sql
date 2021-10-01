-- What is the address, phone number, and account balance
--  of Customer#000000010?
SELECT c_address,
    c_phone,
    c_acctbal
FROM customer
WHERE c_custkey = 10;
-- What is the smallest account balance of a supplier?
SELECT MIN(s_acctbal)
FROM supplier;
-- Find all the line items with the return flag set to R 
-- on the receipt date of August 22, 1993. Print l receiptdate,
--  l returnflag, l extendedprice, and l tax for every line item.
SELECT l_receiptdate,
    l_returnflag,
    l_extendedprice,
    l_tax
FROM lineitem
WHERE l_returnflag = 'R'
    AND l_receiptdate = '1993-08-22';
-- Find the number of line items that have l shipdate smaller than
-- l commitdate.
SELECT COUNT(*)
FROM lineitem
WHERE l_shipdate < l_commitdate;
-- What is the minimum, maximum, and total account balance among
--  the customers in every market segment?
SELECT DISTINCT c_mktsegment,
    min(c_acctbal),
    max(c_acctbal),
    sum(c_acctbal)
FROM customer
GROUP BY c_mktsegment;
-- What are the nations of customers who made orders between
--  September 10-12, 1996? Print every nation only once and 
-- sort them in alphabetical order.
SELECT DISTINCT n_name
FROM customer,
    orders,
    nation
WHERE c_custkey = o_custkey
    AND n_nationkey = c_nationkey
    AND o_orderdate BETWEEN '1996-09-10' AND '1996-09-12'
ORDER BY n_name;
-- How many line items with l receiptdate in 1993 did Customer#000000010 
-- order? Print the number of ordered line items corresponding to every month.
SELECT substr(l_receiptdate, 0, 8),
    COUNT(*)
FROM lineitem,
    customer,
    orders
WHERE o_orderkey = l_orderkey
    AND c_custkey = o_custkey
    AND substr(l_receiptdate, 0, 5) = '1993'
    AND c_name = 'Customer#000000010'
GROUP BY substr(l_receiptdate, 0, 8);
-- Find the name of the suppliers from AMERICA who have more than 
-- $5000 on account balance. 
-- Print the supplier name and their account balance.
SELECT s_name,
    s_acctbal
FROM supplier
    NATURAL JOIN nation
    NATURAL JOIN region
WHERE (
        (r_regionkey = n_regionkey)
        AND (n_nationkey = s_nationkey)
        AND (r_name = 'AMERICA')
        AND (s_acctbal > 5000)
    );
-- Find the maximum account balance of the suppliers from nations 
-- with more than 5 suppliers. Print the nation name, the number 
-- of suppliers from that nation, and the maximum account balance.
SELECT n_name,
    myCount,
    max
FROM (
        SELECT n_name,
            COUNT(*) AS myCount,
            max(s_acctbal) AS max
        FROM nation,
            supplier
        WHERE s_nationkey = n_nationkey
        GROUP BY n_nationkey
    )
WHERE myCount > 5;
-- Find the total price o totalprice of orders made by customers 
-- from AMERICA in 1996.
SELECT sum(o_totalprice)
FROM orders,
    customer,
    nation,
    region
WHERE o_custkey = c_custkey
    AND c_nationkey = n_nationkey
    AND n_regionkey = r_regionkey
    AND r_name = 'AMERICA'
    AND substr(o_orderdate, 0, 5) = '1996';
-- Find the number of customers that received a discount of at least 10% 
-- for one of the line items on their orders. Count every customer exactly 
-- once even if they have multiple discounted line items
SELECT COUNT(DISTINCT c_name)
FROM customer,
    lineitem,
    orders
WHERE c_custkey = o_custkey
    AND o_orderkey = l_orderkey
    AND l_discount >=.1;
-- Find the number of orders having status F. Group these orders based on the 
-- region of the customer who posted the order. Print the region name and the
-- number of status F orders.
SELECT r_name,
    COUNT(o_orderstatus)
FROM orders,
    customer,
    nation,
    region
WHERE c_custkey = o_custkey
    AND c_nationkey = n_nationkey
    AND n_regionkey = r_regionkey
    AND o_orderstatus = 'F'
GROUP BY r_name;
-- Find the total account balance of all the customers
--  from EUROPE in the MACHINERY market segment
SELECT Sum(c_acctbal)
FROM customer,
    nation,
    region
WHERE c_nationkey = n_nationkey
    AND r_regionkey = n_regionkey
    AND r_name = 'EUROPE'
    AND c_mktsegment = 'MACHINERY';
-- Find how many 1-URGENT priority orders have been posted by customers
-- from BRAZIL between 1994 and 1997, combined.
SELECT COUNT(o_orderpriority)
FROM orders,
    nation,
    supplier,
    region,
    lineitem
WHERE s_suppkey = l_suppkey
    AND l_orderkey = o_orderkey
    AND s_nationkey = n_nationkey
    AND r_regionkey = n_regionkey
    AND o_orderpriority = '1-URGENT'
    AND n_name = 'BRAZIL'
    AND Substr(o_orderdate, 0, 5) BETWEEN '1995' AND '1996';
-- Find the total number of line items on orders 
-- with priority 3-MEDIUM supplied by suppliers 
-- from CANADA. Groups these line items based on 
-- the year of the order from o orderdate. Print 
-- the year and the count. Check the substr 
-- function in SQLite.
SELECT Substr(o_orderdate, 0, 5),
    COUNT(o_orderpriority)
FROM orders,
    nation,
    supplier,
    region,
    lineitem
WHERE s_suppkey = l_suppkey
    AND l_orderkey = o_orderkey
    AND s_nationkey = n_nationkey
    AND r_regionkey = n_regionkey
    AND o_orderpriority = '3-MEDIUM'
    AND n_name = 'CANADA'
GROUP BY Substr(o_orderdate, 0, 5),
    n_name;