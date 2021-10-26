-- How many customers are not from EUROPE or AFRICA or ASIA?
SELECT COUNT(*)
FROM customer,
    region,
    nation
WHERE n_nationkey = c_nationkey
    AND n_regionkey = r_regionkey
    AND NOT r_name = 'EUROPE' -- You can probably do this using a subquery 
    AND NOT r_name = 'AFRICA'
    AND NOT r_name = 'ASIA';
-- How many suppliers in every region have less balance 
-- in their account than the average account balance of 
-- their own region ?
SELECT r.r_name,
    COUNT(s_suppkey)
FROM region AS r,
    nation AS n,
    supplier AS s,
    -- Subquery a new table that has the average s_acctbal and regionkey
    (
        SELECT r_regionkey,
            avg(s_acctbal) AS avg
        FROM region,
            supplier,
            nation
        WHERE s_nationkey = n_nationkey
            AND n_regionkey = r_regionkey
        GROUP BY r_name
    ) AS region_avg
WHERE s.s_nationkey = n.n_nationkey
    AND n.n_regionkey = r.r_regionkey
    AND region_avg.r_regionkey = r.r_regionkey
    AND s.s_acctbal < region_avg.avg
GROUP BY r.r_name;
-- For the line items ordered in October 1996 (o_orderdate), 
-- find the smallest discount that is larger than the average 
-- discount among all the orders.
SELECT min(l_discount)
FROM (
        SELECT l_discount
        FROM lineitem AS l,
            (
                SELECT avg(l_discount) AS avg
                FROM lineitem
            ) AS b
        WHERE l.l_discount > b.avg
    ) AS a;
-- How many customers and suppliers are in every country from AFRICA?
SELECT cnation.n_name,
    COUNT(DISTINCT c_custkey),
    COUNT(DISTINCT s_suppkey)
FROM nation AS cnation,
    region AS cregion,
    nation AS snation,
    region AS sregion,
    customer,
    supplier
WHERE c_nationkey = cnation.n_nationkey
    AND cnation.n_regionkey = cregion.r_regionkey
    AND cregion.r_name = 'AFRICA'
    AND s_nationkey = snation.n_nationkey
    AND snation.n_regionkey = sregion.r_regionkey
    AND sregion.r_name = 'AFRICA'
    AND cnation.n_comment = snation.n_comment
GROUP BY cnation.n_name;
-- For parts whose type contains STEEL, return the name of the 
-- supplier from ASIA that can supply them at minimum cost 
-- (ps supplycost), for every part size. Print the supplier name 
-- together with the part size and the minimum cost.
SELECT s_name,
    p_size,
    min(ps_supplycost)
FROM part,
    partsupp,
    supplier,
    nation,
    region
WHERE p_type LIKE '%STEEL%'
    AND p_partkey = ps_partkey
    AND ps_suppkey = s_suppkey
    AND s_nationkey = n_nationkey
    AND n_regionkey = r_regionkey
    AND r_name = 'ASIA'
GROUP BY p_size
ORDER BY s_name;
-- I really don't know why this isn't working because it seems like it should work
-- Based on the available quantity of items, who is the 
-- manufacturer p mfgr of the most popular item (the more
-- popular an item is, the less available it is in ps availqty)
-- from Supplier#000000010?
SELECT p_mfgr
FROM part,
    partsupp,
    supplier,
    (
        SELECT min(ps_availqty) AS miniumum
        FROM part,
            partsupp,
            supplier
        WHERE p_partkey = ps_partkey
            AND ps_suppkey = s_suppkey
            AND s_name = 'Supplier#000000010'
    ) AS minps
WHERE p_partkey = ps_partkey
    AND ps_suppkey = s_suppkey
    AND s_name = 'Supplier#000000010'
    AND ps_availqty <= minps.miniumum;
-- For every order priority, count the number of parts 
-- ordered in 1997 and received later (l receiptdate) 
-- than the commit date (l commitdate).
SELECT o_orderpriority,
    COUNT(o_orderkey)
FROM orders,
    lineitem
WHERE o_orderkey = l_orderkey
    AND strftime('%Y', o_orderdate) = '1997'
    AND DATE(l_receiptdate) > DATE(l_commitdate)
GROUP BY o_orderpriority;
-- Count the number of distinct suppliers that supply parts 
-- whose type contains POLISHED and have size equal to any 
-- of 3, 23, 36, and 49.
SELECT COUNT(DISTINCT s_suppkey)
FROM supplier,
    part,
    partsupp
WHERE s_suppkey = ps_suppkey
    AND ps_partkey = p_partkey
    AND p_type LIKE '%POLISHED%'
    AND p_size IN (3, 23, 36, 49);
-- Print the name of the parts supplied by suppliers 
-- from UNITED STATES that have total value in the top
--  1% total values across all the supplied parts. 
-- The total value is ps supplycost*ps availqty. 
-- Hint: Use the LIMIT keyword.
SELECT p_name
FROM part,
    supplier,
    nation,
    partsupp
WHERE p_partkey = ps_partkey
    AND ps_suppkey = s_suppkey
    AND s_nationkey = n_nationkey
    AND n_name = 'UNITED STATES'
ORDER BY (ps_supplycost * ps_availqty) DESC
LIMIT (
        SELECT COUNT(DISTINCT ps_partkey) / 100
        FROM part,
            partsupp,
            supplier,
            nation
        WHERE p_partkey = ps_partkey
            AND ps_suppkey = s_suppkey
            AND s_nationkey = n_nationkey
            AND n_name = 'UNITED STATES'
    );
-- How many customers from every region have never
-- placed an order and have less than the average
-- account balance?
SELECT r_name,
    COUNT(c_custkey)
FROM customer,
    region,
    nation,
    (
        SELECT avg(c_acctbal) AS avg_cus_acctbal
        FROM customer
    ) AS avgcacctbal
    LEFT JOIN orders ON c_custkey = o_custkey
WHERE o_custkey IS NULL
    AND c_nationkey = n_nationkey
    AND n_regionkey = r_regionkey
    AND c_acctbal < avgcacctbal.avg_cus_acctbal
GROUP BY r_name;
-- Find the lowest value line item(s) (l extendedprice*(1-l discount))
-- shipped after October 2, 1996. Print the name of the part corresponding 
-- to these line item(s).
SELECT DISTINCT p1.p_name
FROM lineitem,
    orders,
    part AS p1,
    (
        SELECT p2.p_partkey,
            min(l_extendedprice *(1 - l_discount)) AS lowvalue
        FROM lineitem,
            orders,
            part AS p2
        WHERE l_orderkey = o_orderkey
            AND l_partkey = p2.p_partkey
            AND strftime('%Y-%m-%d', o_orderdate) > '1996-10-02'
    ) AS minvalueitem
WHERE l_orderkey = o_orderkey
    AND l_partkey = p1.p_partkey
    AND strftime('%Y-%m-%d', o_orderdate) > '1996-10-02'
    AND p1.p_partkey = minvalueitem.p_partkey;
-- What is the total supply cost (ps supplycost) for parts 
-- less expensive than $1000 (p retailprice) shipped in 1997
-- (l shipdate) by suppliers who did not supply any line 
-- item with an extended price less than 2000 in 1996?
SELECT total(ps_supplycost)
FROM partsupp,
    part,
    supplier AS s1,
    lineitem
WHERE ps_partkey = p_partkey
    AND ps_suppkey = s_suppkey
    AND l_partkey = p_partkey
    AND p_retailprice < 1000
    AND strftime('%Y', l_shipdate) = '1997'
    AND NOT EXISTS (
        SELECT *
        FROM supplier AS s2,
            lineitem
        WHERE l_suppkey = s2.s_suppkey
            AND s2.s_name = s1.s_name
            AND l_extendedprice < 2000
            AND strftime('%Y', l_shipdate) = '1996'
    );
-- Count the number of orders made in the fourth 
-- quarter of 1997 in which at least one line item 
-- was received by a customer earlier than its commit
-- date. List the count of such orders for every order priority.
SELECT o_orderpriority,
    COUNT(DISTINCT o_orderkey)
FROM orders,
    lineitem
WHERE o_orderkey = l_orderkey
    AND ((strftime('%m', o_orderdate) + 2) / 3) = 4
    AND strftime('%Y', o_orderdate) = '1997'
    AND strftime('%Y-%m-%d', l_commitdate) > strftime('%Y-%m-%d', l_receiptdate)
GROUP BY o_orderpriority;
-- For any two regions, find the gross discounted revenue
-- (l extendedprice*(1-l discount)) derived from line items
-- in which parts are shipped from a supplier in the first 
-- region to a customer in the second region in 1996 and 1997.
-- List the supplier region, the customer region, the year 
-- (l shipdate), and the revenue from shipments that took place
-- in that year.
SELECT supregion.r_name,
    cusregion.r_name,
    strftime('%Y', l_shipdate),
    total((l_extendedprice *(1 - l_discount)))
FROM region AS supregion,
    nation AS supnation,
    region AS cusregion,
    nation AS cusnation,
    supplier,
    customer,
    lineitem,
    orders
WHERE c_nationkey = cusnation.n_nationkey
    AND cusnation.n_regionkey = cusregion.r_regionkey
    AND s_nationkey = supnation.n_nationkey
    AND supnation.n_regionkey = supregion.r_regionkey
    AND s_suppkey = l_suppkey
    AND c_custkey = o_custkey
    AND o_orderkey = l_orderkey
    AND strftime('%Y', l_shipdate) BETWEEN '1996' AND '1997'
GROUP BY supregion.r_name,
    cusregion.r_name,
    strftime('%Y', l_shipdate);
-- The market share for a given nation within a given 
-- region is defined as the fraction of the revenue 
-- from the line items ordered by customers in the 
-- given region that are supplied by suppliers from 
-- the given nation. The revenue of a line item is 
-- defined as l extendedprice*(1-l discount). Determine 
-- the market share of UNITED STATES in ASIA in 1997 
-- (l shipdate).
WITH totalrevenue AS (
    SELECT sum((l_extendedprice * (1 - l_discount))) AS total
    FROM region AS totalcusregion,
        nation AS totalsupnation,
        nation AS totalcusnation,
        customer,
        supplier,
        lineitem,
        orders
    WHERE c_nationkey = totalcusnation.n_nationkey
        AND totalcusnation.n_regionkey = totalcusregion.r_regionkey
        AND totalcusregion.r_name = 'ASIA'
        AND s_nationkey = totalsupnation.n_nationkey
        AND s_suppkey = l_suppkey
        AND c_custkey = o_custkey
        AND o_orderkey = l_orderkey
        AND strftime('%Y', l_shipdate) = '1997'
)
SELECT round(
        (
            sum(
                (
                    unlineitem.l_extendedprice * (1 - unlineitem.l_discount)
                )
            ) / totalrevenue.total
        ),
        17
    )
FROM region AS cusregion,
    nation AS cusnation,
    nation AS supnation,
    customer AS asiacustomer,
    supplier AS unsupplier,
    lineitem AS unlineitem,
    orders AS asiaorders,
    totalrevenue
WHERE asiacustomer.c_nationkey = cusnation.n_nationkey
    AND cusnation.n_regionkey = cusregion.r_regionkey
    AND cusregion.r_name = 'ASIA'
    AND unsupplier.s_nationkey = supnation.n_nationkey
    AND supnation.n_name = 'UNITED STATES'
    AND unsupplier.s_suppkey = unlineitem.l_suppkey
    AND asiacustomer.c_custkey = asiaorders.o_custkey
    AND asiaorders.o_orderkey = unlineitem.l_orderkey
    AND strftime('%Y', unlineitem.l_shipdate) = '1997'