<?php
	/*
	session_start();
	include("includes/users.php");
	$fname = $_POST["fName"];
	$lname = $_POST["lName"];
	$pic = NULL;
	$path = "pictures/";
	$user = new users();

	if (!empty($_FILES['pic'])) {
		// $path = "pictures/";
		$path = $path . basename($_FILES['pic']['name']);
		if (move_uploaded_file($_FILES['pic']['tmp_name'], $path)) {
			echo "The file " . basename($_FILES['pic']['name']). " has been uploaded.";
		} else {
			echo "There was an error uploading the file, please try again.";
		}
	}

	$pic = $path;
	$user->prepareUserData($fname, $lname, $pic);
	$lastID = $user->saveUserDatav2();

	if ($lastID != FALSE) {
		// $recordID = $user->getLastRecordID();
		echo $lastID;
		$_SESSION['userID'] = $lastID;
		$_SESSION["loggedin"] = TRUE;
		header('Location: simpleProfile.php');
	} else {
		header('Location: index.html');
	}
	*/

	if(isset($_POST['action']) and $_POST['action'] == 'upload') {
		if (!is_uploaded_file($_FILES['upload']['tmp_name'])) {
			$error = 'There was no file uploaded!';
			echo $error;
			exit();
		}

		$uploadfile = $_FILES['upload']['tmp_name'];
		$uploadname = $_FILES['upload']['name'];
		$uploadtype = $_FILES['upload']['type'];
		$uploaddesc = $_POST['desc'];
		$uploaddata = file_get_contents($uploadfile);

		/*
		try {
			$pdo = new PDO('mysql:host=localhost;dbname=binaryData', 'xxxx', 'xxxx');
			$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
			$pdo->exec('SET NAMES "utf8"');
		} catch (PDOException $e) {
			$error = 'Unable to connect to the database server.';
			exit();
		}
		*/

		# we can replace this chunk of code with the following include
		inlcude("includes/database.php");

		try {
			$sql = 'INSERT INTO filestore SET
			id = :id,
			filename = :filename,
			mimetype = :mimetype,
			description = :description,
			filedata = :filedata,';

			$s = $pdo->prepare($sql);
			$s->bindValue(':id', NULL);
			$s->bindValue(':filename', $uploadname);
			$s->bindValue(':mimetype', $uploadtype);
			$s->bindValue(':description', $uploaddesc);
			$s->bindValue(':filedata', $uploaddata);
			$s->execute();

			$lastID = $pdo->lastInsertId();
		} catch (PDOException $e) {
			$error = 'Database error storing file!';
			echo $e;
			exit();
		}
		header('Location: imageLIsting.php?id='.$lastID);
	}
	?>