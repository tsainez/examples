-- Find the total price paid on orders by every customer 
-- from FRANCE in 1995. Print the customer name and the 
-- total price.
SELECT c_name,
    sum(o_totalprice)
FROM orders,
    customer
WHERE o_custkey = c_custkey
    AND c_nationkey = 6
    AND substr(o_orderdate, 0, 5) = '1995'
GROUP BY c_name;
-- Find the number of suppliers from every region.
SELECT r_name,
    COUNT(*)
FROM supplier,
    region,
    nation
WHERE n_regionkey = r_regionkey
    AND s_nationkey = n_nationkey
GROUP BY r_name;
-- How many orders are posted by customers in every country in AMERICA?
SELECT n_name,
    COUNT(*)
FROM orders,
    nation,
    region,
    customer
WHERE c_nationkey = n_nationkey
    AND r_regionkey = n_regionkey
    AND o_custkey = c_custkey
    AND r_name = 'AMERICA'
GROUP BY n_name;
-- How many parts with size below 20 does every supplier from CANADA offer?
-- Print the name of the supplier and the number of parts.
SELECT s_name,
    COUNT(*)
FROM supplier,
    part,
    nation,
    partsupp
WHERE s_nationkey = n_nationkey
    AND s_suppkey = ps_suppkey
    AND ps_partkey = p_partkey
    AND n_name = 'CANADA'
    AND p_size < 20
GROUP BY s_name;
-- Find the number of orders posted by every customer from GERMANY in 1993.
SELECT c_name,
    COUNT(*)
FROM customer,
    nation,
    orders
WHERE c_custkey = o_custkey
    AND c_nationkey = n_nationkey
    AND n_name = 'GERMANY'
    AND substr(o_orderdate, 0, 5) = '1993'
GROUP BY c_name;
-- How many unique parts produced by every supplier in CANADA are ordered 
-- at every priority? Print the supplier name, the order priority, and the 
-- number of parts.
SELECT s_name,
    o_orderpriority,
    COUNT(DISTINCT p_name)
FROM supplier,
    orders,
    nation,
    part,
    lineitem
WHERE s_suppkey = l_suppkey
    AND l_partkey = p_partkey
    AND s_nationkey = n_nationkey
    AND o_orderkey = l_orderkey
    AND n_name = 'CANADA'
GROUP BY s_name,
    o_orderpriority;
-- How many orders do customers in every nation in AMERICA have in every status? 
-- Print the nation name, the order status, and the count.
SELECT n_name,
    o_orderstatus,
    COUNT(*)
FROM customer,
    orders,
    nation,
    region
WHERE c_custkey = o_custkey
    AND n_regionkey = r_regionkey
    AND r_name = 'AMERICA'
    AND n_nationkey = c_nationkey
GROUP BY n_name,
    o_orderstatus;
-- Find the number of distinct orders completed in 1995 by the suppliers in every
-- nation. An order status of F stands for complete. Print only those nations for
-- which the number of orders is larger than 50.
SELECT n_name,
    COUNT(DISTINCT l_orderkey)
FROM orders,
    supplier,
    nation,
    region,
    lineitem
WHERE s_nationkey = n_nationkey
    AND n_regionkey = r_regionkey
    AND l_suppkey = s_suppkey
    AND o_orderkey = l_orderkey
    AND o_orderstatus = 'F'
    AND substr(o_orderdate, 0, 5) = '1995'
GROUP BY n_name
HAVING COUNT(DISTINCT l_orderkey) > 50;
-- How many different order clerks did the suppliers in UNITED STATES work with?
SELECT COUNT(DISTINCT o_clerk)
FROM nation,
    supplier,
    orders,
    lineitem
WHERE n_name = 'UNITED STATES'
    AND o_orderkey = l_orderkey
    AND n_nationkey = s_nationkey
    AND l_suppkey = s_suppkey;
-- Find the minimum and maximum discount for every part having 
-- ECONOMY and COPPER in its type.
SELECT p_type,
    min(l_discount),
    max(l_discount)
FROM part,
    lineitem
WHERE p_partkey = l_partkey
    AND p_type LIKE 'ECONOMY%'
    AND p_type LIKE "%COPPER"
GROUP BY p_type;
-- Find the supplier with the largest account balance in every region.
-- Print the region name, the supplier name, and the account balance.
SELECT r_name,
    s_name,
    s_acctbal
FROM region,
    supplier,
    nation
WHERE r_regionkey = n_regionkey
    AND s_nationkey = n_nationkey
GROUP BY r_name
HAVING MAX(s_acctbal);
-- What is the maximum account balance for the suppliers in every nation? 
-- Print only those nations for which the maximum balance is larger than 9000.
SELECT n_name,
    MAX(s_acctbal)
FROM region,
    nation,
    supplier
WHERE n_nationkey = s_nationkey
    AND r_regionkey = n_regionkey
GROUP BY n_name
HAVING MAX(s_acctbal) > 9000;
-- How many line items are supplied by suppliers in AFRICA 
-- for orders made by customers in UNITED STATES?
SELECT COUNT(*)
FROM supplier,
    nation AS s,
    region,
    lineitem,
    orders,
    customer,
    nation AS c
WHERE s_nationkey = s.n_nationkey
    AND s.n_regionkey = r_regionkey
    AND r_name = 'AFRICA'
    AND l_suppkey = s_suppkey
    AND l_orderkey = o_orderkey
    AND o_custkey = c_custkey
    AND c.n_nationkey = c_nationkey
    AND c.n_name = 'UNITED STATES';
-- List the maximum total price of an order between any two regions, 
-- i.e., the suppliers are from one region and the customers are from 
-- the other region.
SELECT s.r_name,
    c.r_name,
    max(o_totalprice)
FROM region AS c,
    region AS s,
    nation AS cn,
    nation AS sn,
    lineitem,
    supplier,
    orders,
    customer
WHERE l_suppkey = s_suppkey
    AND s_nationkey = sn.n_nationkey
    AND sn.n_regionkey = s.r_regionkey
    AND l_orderkey = o_orderkey
    AND o_custkey = c_custkey
    AND c_nationkey = cn.n_nationkey
    AND cn.n_regionkey = c.r_regionkey
GROUP BY s.r_name,
    c.r_name;
-- How many distinct orders are between customers with positive account 
-- balance and suppliers with negative account balance?
SELECT COUNT(DISTINCT o_orderkey)
FROM orders,
    customer,
    lineitem,
    supplier
WHERE s_suppkey = l_suppkey
    AND o_orderkey = l_orderkey
    AND c_custkey = o_custkey
    AND s_acctbal < 0
    AND c_acctbal > 0;