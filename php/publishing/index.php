<?php

	try {
	     $dbHost = getenv('DB_HOST') ?: 'localhost';
	     $dbName = getenv('DB_NAME') ?: 'ijdb';
	     $dbUser = getenv('DB_USER') !== false ? getenv('DB_USER') : 'ijdb';
	     $dbPass = getenv('DB_PASS') !== false ? getenv('DB_PASS') : '';

	     $pdo = new PDO("mysql:host=$dbHost;dbname=$dbName", $dbUser, $dbPass);

	     $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

	     $pdo->exec('SET NAMES "utf8"');

	}

	catch (PDOException $e) {

	     $error = 'Unable to connect to the database server.';

	     include 'error.html.php';

	     exit();

	}

	try {

	     $sql = 'SELECT joketext FROM joke';

	     $result = $pdo->query($sql);

	}

	catch (PDOException $e) {

	     $error = 'Error fetching jokes: ' . $e->getMessage();

	     include 'error.html.php';

	     exit();

	}

	while ($row = $result->fetch()) {

	     $jokes[] = $row['joketext'];

	}

	include 'jokes.html.php';

?>