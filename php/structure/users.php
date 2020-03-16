<?php
	# echo '<strong>users.php</strong>';

	# users.php
	# connect to db and print all users in user table 

	include 'menu.php';
	echo '<h2> Users </h2>';
	
	include 'database.inc.php';

	try {
		$results = $pdo->query("SELECT * FROM users ORDER BY userid ASC");
		echo "Successful operation acquiring table.";
	} catch (Exception $e) {
		echo "Fatal error fecthing table";
		# exit;
		# commented it out because we don't actually want it to be fatal
	}

	echo "<pre>";
	var_dump($results->fetchAll(PDO::FETCH_ASSOC));
	echo "</pre>";

	include 'footer.php';

?>