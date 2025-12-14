<?php
/**
 * Calculates and prints the Fibonacci sequence up to a given position.
 *
 * Receives a position 'input' from a POST request, generates the Fibonacci
 * sequence up to that index, and displays the resulting array.
 *
 * @param int $_POST['input'] The position in the Fibonacci sequence to calculate up to.
 */

	$pos = $_POST['input'];

	$fibarray = array(0, 1);

	for ($i=2; $i<=$pos; ++$i ){
		$fibarray[$i] = $fibarray[$i-1] + $fibarray[$i-2];
	}

    echo '<pre>';
    var_dump($fibarray);
    echo '</pre>';

	// return $fibarray;
?>