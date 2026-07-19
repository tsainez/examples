<?php
     $userName = $_POST["uName"];
     $password = $_POST["myPassword"];

     $dbHost = getenv('DB_HOST') ?: '127.0.0.1';
     $dbName = getenv('DB_NAME') ?: 'lab10';
     $dbUser = getenv('DB_USER');
     $dbPass = getenv('DB_PASS');

     $pdo = new PDO("mysql:host=$dbHost;dbname=$dbName", $dbUser, $dbPass);

     $queryString = "INSERT INTO `users` (`username`, `password`) VALUES (:username, :password)";

     $result = $pdo->prepare($queryString);
     $result->execute(['username' => $userName, 'password' => $password]);
?>