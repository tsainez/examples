<?php
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