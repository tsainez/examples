-- Find the total quantity (l quantity) of line items shipped per month (l shipdate) 
-- in 1995. Hint: check function strftime to extract the month/year from a date.
SELECT substr(l_shipdate, 6, 2),
    sum(l_quantity)
FROM lineitem
WHERE substr(l_shipdate, 0, 5) = '1995'
GROUP BY substr(l_shipdate, 6, 2);
-- Find the number of customers who had at least three orders in November 1995 (o orderdate).
SELECT COUNT(*)
FROM (
        SELECT COUNT(*) AS COUNT
        FROM orders
        WHERE substr(o_orderdate, 0, 8) = '1995-11'
        GROUP BY o_custkey
    ) AS a
WHERE a.count >= 3;
-- Find how many parts are supplied by exactly two suppliers from UNITED STATES.
SELECT COUNT(*)
FROM (
        SELECT COUNT(s_name) AS COUNT,
            p_name
        FROM part,
            partsupp,
            supplier,
            nation
        WHERE p_partkey = ps_partkey
            AND ps_suppkey = s_suppkey
            AND s_nationkey = n_nationkey
            AND n_name = 'UNITED STATES'
        GROUP BY p_name
    ) AS a
WHERE a.count = 2;
-- Find how many suppliers from UNITED STATES supply more than 40 different parts.
SELECT COUNT(*)
FROM (
        SELECT s_name,
            COUNT(p_name) AS COUNT
        FROM part,
            partsupp,
            supplier,
            nation
        WHERE p_partkey = ps_partkey
            AND ps_suppkey = s_suppkey
            AND s_nationkey = n_nationkey
            AND n_name = 'UNITED STATES'
        GROUP BY s_name
    ) AS a
WHERE a.count > 40;
-- Find how many suppliers supply the most expensive part (p retailprice).
SELECT COUNT(*)
FROM partsupp,
    supplier,
    (
        SELECT p_partkey AS p,
            max(p_retailprice)
        FROM part
    ) AS a
WHERE ps_partkey = a.p
    AND ps_suppkey = s_suppkey;
-- Find the supplier-customer pair(s) with the least expensive
-- (o totalprice) order(s) completed (F in o orderstatus). 
-- Print the supplier name, the customer name, and the total price.
SELECT s_name,
    c_name,
    min(o_totalprice)
FROM supplier,
    customer,
    orders,
    lineitem
WHERE c_custkey = o_custkey
    AND o_orderkey = l_orderkey
    AND l_suppkey = s_suppkey;
-- Find how many suppliers have less than 50 distinct orders 
-- from customers in GERMANY and FRANCE together.
SELECT COUNT(*)
FROM (
        SELECT COUNT(o_orderkey) AS COUNT
        FROM orders,
            customer,
            nation,
            lineitem,
            supplier
        WHERE o_custkey = c_custkey
            AND c_nationkey = n_nationkey
            AND (
                n_name = 'GERMANY'
                OR n_name = 'FRANCE'
            )
            AND o_orderkey = l_orderkey
            AND l_suppkey = s_suppkey
        GROUP BY s_suppkey
    ) AS a
WHERE a.count <= 50;
-- Find  how  many  distinct  customers  have  at  least  one  
-- order  supplied  exclusively  by  suppliers  from AMERICA.
SELECT COUNT(DISTINCT(c_custkey))
FROM orders,
    customer
WHERE c_custkey = o_custkey
    AND o_orderkey NOT IN (
        -- The NOT IN operator is used when you want to retrieve a column 
        -- that has no entries in the table or referencing table.
        -- So we want o_orderkeys that were not in this reference table that
        -- we are creating in this subquery, where r_name is NOT 'AMERICA'
        SELECT DISTINCT(o_orderkey)
        FROM nation,
            region,
            supplier,
            lineitem,
            orders
        WHERE r_regionkey = n_regionkey -- This part should look normal...
            AND n_nationkey = s_nationkey
            AND s_suppkey = l_suppkey
            AND o_orderkey = l_orderkey
            AND r_name NOT IN ('AMERICA') -- Except for this bit. So to explain...
    );
-- We are looking for all the distinct c_custkeys in the original tables that ALSO
-- are NOT IN a new table we created (which does not have any o_orderkeys tied to 'AMERICA')
-- Find the distinct parts (pname) ordered by customers from
-- AMERICA that are supplied by exactly 3 suppliers from ASIA
SELECT DISTINCT p1.p_name
FROM lineitem,
    part AS p1,
    (
        -- All p_partkeys from 'AMERICA'
        SELECT p_partkey
        FROM orders,
            customer,
            nation,
            region,
            lineitem,
            part
        WHERE c_custkey = o_custkey
            AND o_orderkey = l_orderkey
            AND l_partkey = p_partkey
            AND c_nationkey = n_nationkey
            AND n_regionkey = r_regionkey
            AND r_name = 'AMERICA'
    ) AS t2,
    (
        -- Table containing all p_partkeys that are 
        -- supplied by 3 suppliers from 'ASIA'.
        SELECT p_partkey
        FROM supplier,
            nation,
            region,
            lineitem,
            part
        WHERE p_partkey = l_partkey
            AND l_suppkey = s_suppkey
            AND s_nationkey = n_nationkey
            AND n_regionkey = r_regionkey
            AND r_name = 'ASIA'
        GROUP BY p_partkey
        HAVING COUNT(*) = 3
    ) AS t1
WHERE l_partkey = t1.p_partkey -- Basically what this is doing is that it 
    AND l_partkey = t2.p_partkey -- makes sure we are talking about the same part.
    AND l_partkey = p1.p_partkey;
-- Find the region where customers spend the smallest amount of money 
-- (l extendedprice) buying items from suppliers in the same region.
SELECT b.sub_name
FROM (
        SELECT min(a.sum),
            a.sub_name AS sub_name
        FROM (
                SELECT sum(l_extendedprice) AS sum,
                    r_name AS sub_name
                FROM lineitem,
                    orders,
                    customer,
                    nation AS c,
                    nation AS s,
                    region,
                    supplier
                WHERE l_orderkey = o_orderkey
                    AND l_suppkey = s_suppkey
                    AND o_custkey = c_custkey
                    AND c_nationkey = c.n_nationkey
                    AND c.n_regionkey = r_regionkey
                    AND s_nationkey = s.n_nationkey
                    AND s.n_regionkey = r_regionkey
                    AND c.n_regionkey = s.n_regionkey
                GROUP BY r_name
            ) AS a
    ) AS b;
-- Find the nation(s) with the smallest number of customers.
SELECT name_min.name
FROM (
        SELECT n_name AS name,
            min(nationkey_count.count)
        FROM nation,
            (
                SELECT c_nationkey AS nationkey,
                    COUNT(c_nationkey) AS COUNT
                FROM customer
                GROUP BY c_nationkey
            ) AS nationkey_count
        WHERE n_nationkey = nationkey_count.nationkey
    ) AS name_min;
-- Find the nation(s) having customers that spend the 
-- smallest amount of money (o totalprice).
SELECT n_name
FROM nation,
    (
        SELECT min(nationkey_totalprice.totalprice) AS min,
            nationkey_totalprice.nationkey AS nationkey
        FROM (
                SELECT c_nationkey AS nationkey,
                    sum(o_totalprice) AS totalprice
                FROM orders,
                    customer
                WHERE o_custkey = c_custkey
                GROUP BY c_nationkey
            ) AS nationkey_totalprice
    ) AS min_nationkey
WHERE min_nationkey.nationkey = n_nationkey;
-- Find the nation(s) with the most developed industry, 
-- i.e., selling items totaling the largest amount of 
-- money (l extendedprice) in 1994 (l shipdate).
SELECT max_name.name
FROM (
        SELECT max(sum_name.sum) AS max,
            name AS name
        FROM (
                SELECT sum(l_extendedprice) AS sum,
                    n_name AS name
                FROM lineitem,
                    supplier,
                    nation
                WHERE l_suppkey = s_suppkey
                    AND s_nationkey = n_nationkey
                    AND substr(l_shipdate, 0, 5) = '1994'
                GROUP BY n_nationkey
            ) AS sum_name
    ) AS max_name;
-- Compute, for every country, the value of economic exchange, 
-- i.e., the difference between the number of items from suppliers
-- in that country sold to customers in other countries and the
-- number of items bought by local customers from foreign suppliers
-- in 1994 (lshipdate).
SELECT name2,
    -- Shouldn't matter if we chose name2 or name1
    (cont1 - cont2)
FROM (
        SELECT n_name AS name1,
            COUNT(l_extendedprice) AS cont1
        FROM customer,
            orders,
            lineitem,
            supplier,
            nation
        WHERE c_custkey = o_custkey
            AND l_suppkey = s_suppkey
            AND l_orderkey = o_orderkey
            AND s_nationkey = n_nationkey
            AND s_nationkey != c_nationkey
            AND strftime('%Y', l_shipdate) = '1994'
        GROUP BY n_name
    ),
    (
        SELECT n_name AS name2,
            COUNT(l_extendedprice) AS cont2
        FROM customer,
            orders,
            lineitem,
            supplier,
            nation
        WHERE c_custkey = o_custkey
            AND l_suppkey = s_suppkey
            AND l_orderkey = o_orderkey
            AND c_nationkey = n_nationkey -- NOTE: This part varies
            AND s_nationkey != c_nationkey
            AND strftime('%Y', l_shipdate) = '1994'
        GROUP BY n_name
    )
WHERE name1 = name2;
-- Ensure we are talking about the same nation
-- Compute the change in the economic exchange for every country 
-- between 1994 and 1996. There should be two columns in the output
-- for every country: 1995 and 1996.
-- Hint: use CASE to select the values in the result.
-- This is kind of a brute force way to do it, I am not sure how to do it using
-- a CASE statement. 
SELECT t1.name1,
    (change95 - change94),
    (change96 - change95)
FROM (
        -- This is basically expanding out the previous question but by 2x
        -- You do #14 but for more years and then just add another column manually.
        SELECT name1,
            (cont1 - cont2) AS change94
        FROM (
                SELECT n_name AS name1,
                    COUNT(l_extendedprice) AS cont1
                FROM customer,
                    orders,
                    lineitem,
                    supplier,
                    nation
                WHERE c_custkey = o_custkey
                    AND l_suppkey = s_suppkey
                    AND l_orderkey = o_orderkey
                    AND s_nationkey = n_nationkey
                    AND c_nationkey != s_nationkey
                    AND strftime('%Y', l_shipdate) = '1994'
                GROUP BY n_name
            ),
            (
                SELECT n_name AS name2,
                    COUNT(l_extendedprice) AS cont2
                FROM customer,
                    orders,
                    lineitem,
                    supplier,
                    nation
                WHERE c_custkey = o_custkey
                    AND c_nationkey = n_nationkey
                    AND l_suppkey = s_suppkey
                    AND l_orderkey = o_orderkey
                    AND s_nationkey != c_nationkey
                    AND strftime('%Y', l_shipdate) = '1994'
                GROUP BY n_name
            )
        WHERE name1 = name2
    ) AS t1,
    (
        SELECT name1,
            (cont1 - cont2) AS change95
        FROM (
                SELECT n_name AS name1,
                    COUNT(l_extendedprice) AS cont1
                FROM customer,
                    orders,
                    lineitem,
                    supplier,
                    nation
                WHERE c_custkey = o_custkey
                    AND l_suppkey = s_suppkey
                    AND l_orderkey = o_orderkey
                    AND s_nationkey = n_nationkey
                    AND c_nationkey != s_nationkey
                    AND strftime('%Y', l_shipdate) = '1995'
                GROUP BY n_name
            ),
            (
                SELECT n_name AS name2,
                    COUNT(l_extendedprice) AS cont2
                FROM customer,
                    orders,
                    lineitem,
                    supplier,
                    nation
                WHERE c_custkey = o_custkey
                    AND c_nationkey = n_nationkey
                    AND l_suppkey = s_suppkey
                    AND l_orderkey = o_orderkey
                    AND s_nationkey != c_nationkey
                    AND strftime('%Y', l_shipdate) = '1995'
                GROUP BY n_name
            )
        WHERE name1 = name2
    ) AS t2,
    (
        SELECT name1,
            (cont1 - cont2) AS change96
        FROM (
                SELECT n_name AS name1,
                    COUNT(l_extendedprice) AS cont1
                FROM customer,
                    orders,
                    lineitem,
                    supplier,
                    nation
                WHERE c_custkey = o_custkey
                    AND l_suppkey = s_suppkey
                    AND l_orderkey = o_orderkey
                    AND s_nationkey = n_nationkey
                    AND c_nationkey != s_nationkey
                    AND strftime('%Y', l_shipdate) = '1996'
                GROUP BY n_name
            ),
            (
                SELECT n_name AS name2,
                    COUNT(l_extendedprice) AS cont2
                FROM customer,
                    orders,
                    lineitem,
                    supplier,
                    nation
                WHERE c_custkey = o_custkey
                    AND c_nationkey = n_nationkey
                    AND l_suppkey = s_suppkey
                    AND l_orderkey = o_orderkey
                    AND s_nationkey != c_nationkey
                    AND strftime('%Y', l_shipdate) = '1996'
                GROUP BY n_name
            )
        WHERE name1 = name2
    ) AS t3
WHERE t1.name1 = t2.name1
    AND t2.name1 = t3.name1;