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

	if (isset($results) && $results) {
		$users = $results->fetchAll(PDO::FETCH_ASSOC);
		echo "<ul>\n";
		foreach ($users as $user) {
			echo "<li>\n";
			foreach ($user as $key => $value) {
				if (stripos($key, 'password') !== false) {
					continue; // Skip sensitive fields
				}
				echo htmlspecialchars($key) . ": " . htmlspecialchars((string)$value) . "<br>\n";
			}
			echo "</li>\n";
		}
		echo "</ul>\n";
	}

	include 'footer.php';

?>