<?php
	include('includes/users.php');
	session_start;

	$profileID = $_SESSION['userID'];
	$user = new users();
	$user->getRecordByID($profileID);

?>  

<html>
	<head>
		<title>Simple Profile Page</title>
	</head>
	<body>
		<h2>First name: <?php echo $user->getfName(); ?> </h2>
		<h2>Last name: <?php echo $user->getlName(); ?> </h2>
		<h2>Email: <?php echo $user->getEmail(); ?></h2>
		<!-- It is a terrible, terrible, terrilbe idea to ever display someone's password in plaintext, especially on a webpage, but as per requirements of this assignment, we're going to do exactly that. -->
		<h2>Password: <?php echo $user->getPassword(); ?></h2>
		<img alt="User Pic" src="<?php echo $user->getProfilePic()?>" width="200">
	</body>
</html>

