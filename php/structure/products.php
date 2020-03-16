<?php
	# echo '<strong>products.php</strong>';

	# products.php
	# connect to db and print list of all products in product table

	include 'menu.php';	
	echo '<h2> Products </h2>';

	include 'database.inc.php';

	try {
		$results = $pdo->query("SELECT * FROM products ORDER BY productid ASC");
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