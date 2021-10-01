-- SQLite
.headers on

-- You should test that your code works without errors by running the command 
--         sqlite3 data.sqlite < quiz-1.sql 
-- in the terminal. quiz-1.sql is the only file you have to turn in.

--1
-- What makers produce color Printers cheaper than $120?
SELECT DISTINCT maker 
FROM   product 
       INNER JOIN printer 
               ON printer.model = product.model 
WHERE  printer.price < 120 
       AND printer.color = 1 
       AND product.type = 'printer';

--2
-- What makers produce PCs but do not produce Laptops and Printers?

-- from 6.2.2 c), this finds makers that sell Laptops, but not PC’s.
-- SELECT maker
--     FROM Product
--     WHERE type = 'laptop'
-- EXCEPT
--     SELECT maker
--     FROM Product
--     WHERE type = 'pc';

SELECT maker 
    FROM Product 
    WHERE type = 'pc' 
EXCEPT 
    SELECT maker 
    FROM Product 
    WHERE type = 'laptop' OR type = 'printer';

--3
-- For every maker that sells both PCs and Laptops, 
-- find the combination of PC and Laptop that has maximum price. 
-- Print the maker, the PC model, Laptop model, and the combination price 
-- (PC price + Laptop price).

-- From Lecture 9 Slide 8...
-- Find the (PCs, laptop) pairs produced by the same maker for which the PC 
-- price is larger than the laptop price
-- SELECT P1.maker, 
--        pc.model AS pc_model, 
--        L.model  AS laptop_model 
-- FROM   product P1, 
--        product P2, 
--        pc, 
--        laptop L 
-- WHERE  P1.maker = P2.maker 
--        AND P1.model = pc.model 
--        AND P2.model = L.model 
--        AND pc.price > L.price;

SELECT P1.maker, 
       pc.model,
       L.model,
       MAX(pc.price + l.price)
FROM   product P1, 
       product P2, 
       pc, 
       laptop L 
WHERE  P1.maker = P2.maker 
       AND P1.model = pc.model 
       AND P2.model = L.model
GROUP BY P1.maker;

--4
-- What Laptop screen sizes are offered in at least 2 different models?
-- make sure you select screen from laptop and make sure to group by them having a count >= 2
SELECT screen FROM Laptop
GROUP BY screen
HAVING COUNT(model) >= 2;

--5
-- What Laptops are more expensive than all the PCs? Print the model and the price.
SELECT DISTINCT Laptop.model, Laptop.price FROM Laptop, PC 
GROUP BY Laptop.model, Laptop.price
HAVING Laptop.price > MAX(PC.price);

--6
-- What makers produce at least a PC or Laptop model and at least 2 Printer models?
SELECT DISTINCT maker FROM Product
GROUP BY maker
HAVING (COUNT(type = 'pc') > 0 OR COUNT(type = 'laptop')) AND (COUNT(type = 'printer') > 2)