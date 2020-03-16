<?php

class database {
	private $connection;

	public function connect_to_database() {
		# assumes you set the username to lab8

		# try {

			$this->connection = new PDO('msql:host=localhost;dbname=lab8', 'lab8');

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