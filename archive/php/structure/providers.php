<?php
	# echo '<strong>providers.php</strong>';

	# providers.php
	# connect to db and print list of all providers in provider table

	include 'menu.php';	
	echo '<h2> Providers </h2>';

	include 'database.inc.php';

	try {
		$results = $pdo->query("SELECT * FROM providers ORDER BY providerid ASC");
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