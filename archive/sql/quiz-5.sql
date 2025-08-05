PRAGMA foreign_keys = ON;
SELECT "1----------";
.headers ON --put your code here
DROP TABLE IF EXISTS classes;
DROP TABLE IF EXISTS ships;
DROP TABLE IF EXISTS battles;
DROP TABLE IF EXISTS outcomes;
CREATE TABLE IF NOT EXISTS classes(
    class char(32) NOT NULL,
    TYPE char(2) NOT NULL,
    country char(16) NOT NULL,
    numGuns Integer NOT NULL,
    bore Integer NOT NULL,
    displacement Integer NOT NULL,
    PRIMARY KEY (class),
    CHECK(
        TYPE = 'bb'
        OR TYPE = 'bc'
    )
);
CREATE TABLE IF NOT EXISTS ships(
    name char(32) NOT NULL,
    class char(32),
    launched Integer NOT NULL,
    PRIMARY KEY(name),
    FOREIGN KEY (class) REFERENCES classes(class) ON DELETE
    SET NULL ON UPDATE CASCADE
);
CREATE TABLE IF NOT EXISTS battles(
    name char(32) NOT NULL,
    date date NOT NULL,
    PRIMARY KEY (name)
);
CREATE TABLE IF NOT EXISTS outcomes(
    ship char(32) NOT NULL,
    battle char(32) NOT NULL,
    result char(32) NOT NULL,
    PRIMARY KEY (ship, battle),
    FOREIGN KEY (ship) REFERENCES ships(name) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (battle) REFERENCES battles(name) ON DELETE CASCADE ON UPDATE CASCADE,
    ON UPDATE CASCADE,
    CHECK(result IN ('ok', 'sunk', 'damaged'))
);
.headers off
SELECT "2----------";
.headers ON --put your code here
INSERT INTO classes
VALUES('Bismarck', 'bb', 'Germany', 8, 15, 42000),
    ('Iowa', 'bb', 'USA', 9, 16, 46000),
    ('Kongo', 'bc', 'Japan', 8, 14, 32000),
    ('North Carolina', 'bb', 'USA', 9, 16, 37000),
    ('Renown', 'bc', 'Britain', 6, 15, 32000),
    ('Revenge', 'bb', 'Britain', 8, 15, 29000),
    ('Tennessee', 'bb', 'USA', 12, 14, 32000),
    ('Yamato', 'bb', 'Japan', 9, 18, 65000);
INSERT INTO ships
VALUES('California', 'Tennessee', 1915),
    ('Haruna', 'Kongo', 1915),
    ('Hiei', 'Kongo', 1915),
    ('Iowa', 'Iowa', 1933),
    ('Kirishima', 'Kongo', 1915),
    ('Kongo', 'Kongo', 1913),
    ('Missouri', 'Iowa', 1935),
    ('Musashi', 'Yamato', 1942),
    ('New Jersey', 'Iowa', 1936),
    ('North Carolina', 'North Carolina', 1941),
    ('Ramillies', 'Revenge', 1917),
    ('Renown', 'Renown', 1916),
    ('Repulse', 'Renown', 1916),
    ('Resolution', 'Revenge', 1916),
    ('Revenge', 'Revenge', 1916),
    ('Royal Oak', 'Revenge', 1916),
    ('Royal Sovereign', 'Revenge', 1916),
    ('Tennessee', 'Tennessee', 1915),
    ('Washington', 'North Carolina', 1941),
    ('Wisconsin', 'Iowa', 1940),
    ('Yamato', 'Yamato', 1941);
INSERT INTO battles
VALUES('Denmark Strait', '1941-05-24'),
    ('Guadalcanal', '1942-11-15'),
    ('North Cape', '1943-12-26'),
    ('Surigao Strait', '1944-10-25');
INSERT INTO outcomes
VALUES('California', 'Suriago Strait', 'ok'),
    ('Kirishima', 'Guadalcanal', 'sunk'),
    ('Resolution', 'Denmark Strait', 'ok'),
    ('Wisconsin', 'Guadalcanal', 'damaged'),
    ('Tennessee', 'Suriago Strait', 'ok'),
    ('Washington', 'Guadalcanal', 'ok'),
    ('New Jersey', 'Suriago Strait', 'ok'),
    ('Yamato', 'Suriago Strait', 'sunk'),
    ('Wisconsin', 'Suriago Strait', 'damaged');
SELECT *
FROM Classes;
SELECT *
FROM Ships;
SELECT *
FROM Battles;
SELECT *
FROM Outcomes;
.headers off
SELECT "3----------";
.headers ON --put your code here
;
DELETE FROM CLASSES
WHERE displacement < 30000
    OR numGuns < 8;
SELECT *
FROM Classes;
SELECT *
FROM Ships;
.headers off
SELECT "4----------";
.headers ON --put your code here
;
DELETE FROM Battles
WHERE name = "Guadalcanal";
SELECT *
FROM Battles;
SELECT *
FROM Outcomes;
.headers off
SELECT "5----------";
.headers ON --put your code here
;
UPDATE battles
SET name = "Strait of Surigao"
WHERE name = "Surigao Strait";
SELECT *
FROM Battles;
SELECT *
FROM Outcomes;
.headers off
SELECT "6----------";
.headers ON --put your code here
;
DELETE FROM ships
WHERE class IS NULL;
SELECT *
FROM Ships;
SELECT *
FROM Outcomes;
.headers off