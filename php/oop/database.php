<?php

class database {
	private $connection;

	public function connect_to_database() {
		# assumes you set the username to lab8

		# try {

			$db_host = getenv('DB_HOST') ?: 'localhost';
			$db_name = getenv('DB_NAME') ?: 'lab8';
			$db_user = getenv('DB_USER');
			$db_pass = getenv('DB_PASS');

			$this->connection = new PDO("msql:host=$db_host;dbname=$db_name", $db_user, $db_pass);

		/* 
		} catch (PDOException $e) {

			$error = 'Unable to connect to the database server.';

			include 'error.html.php';

			exit();

		}
		*/

	}

	public function run_query($queryString) {
		$output = $this->connection->prepare($queryString);
	
		$output->execute();
	}
}

?>