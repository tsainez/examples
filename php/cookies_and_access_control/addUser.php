<?php
     $userName = $_POST["uName"];
     $password = $_POST["myPassword"];

     $host = getenv('DB_HOST');
     $db = getenv('DB_NAME');
     $user = getenv('DB_USER');
     $pass = getenv('DB_PASS');

     $pdo = new PDO("mysql:host=$host;dbname=$db", $user, $pass);

     $queryString = "INSERT INTO users (username, password) VALUES (:username, :password)";

     $result = $pdo->prepare($queryString);
     $result->execute([
         ':username' => $userName,
         ':password' => $password
     ]);
?>