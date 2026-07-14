<?php
     $userName = $_POST["uName"];
     $password = $_POST["myPassword"];

     // Hash the password securely
     $hashedPassword = password_hash($password, PASSWORD_DEFAULT);

     $pdo = new PDO('mysql:host=192.168.64.2;db=lab10', 'lab10', 'lab10');

     // Use prepared statements with parameter binding to prevent SQL injection
     $queryString = "INSERT INTO users (username, password) VALUES (:username, :password)";
     $result = $pdo->prepare($queryString);
     $result->bindParam(':username', $userName);
     $result->bindParam(':password', $hashedPassword);
     $result->execute();
?>