<?php
	/*
	# echo '<strong>database.inc.php</strong>';

	# database.php
	# in charge of connecting to database
	# every time you need access to the database you include this file

	try {

		$db_host = getenv('DB_HOST') ?: '192.168.64.2';
		$db_name = getenv('DB_NAME') ?: 'inventory';
		$db_user = getenv('DB_USER');
		$db_pass = getenv('DB_PASS');
		$pdo = new PDO("mysql:host=$db_host;dbname=$db_name", (string)$db_user, (string)$db_pass);

		$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

		$pdo->exec('SET NAMES "utf8"');

	} catch (PDOException $e) {

		$error = 'Unable to connect to the database server.';

		include 'error.html.php';

		exit();

	}

	# include 'database.inc.php'
	*/

	try {
		$db_host = getenv('DB_HOST') ?: 'localhost';
		$db_name = getenv('DB_NAME') ?: 'binaryData';
		$db_user = getenv('DB_USER');
		$db_pass = getenv('DB_PASS');
		$pdo = new PDO("mysql:host=$db_host;dbname=$db_name", (string)$db_user, (string)$db_pass);
		$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		$pdo->exec('SET NAMES "utf8"');
	} catch (PDOException $e) {
		$error = 'Unable to connect to the database server.';
		exit();
	}
	?>

