<?php
	# echo '<strong>database.inc.php</strong>';

	# database.php
	# in charge of connecting to database
	# every time you need access to the database you include this file

	try {

		$pdo = new PDO('mysql:host=192.168.64.2;dbname=inventory', 'inventory', '123');

		$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

		$pdo->exec('SET NAMES "utf8"');

	} catch (PDOException $e) {

		$error = 'Unable to connect to the database server.';

		include 'error.html.php';

		exit();

	}

	# include 'database.inc.php'

?>