<?php
     $userName = $_POST["uName"];
     $password = $_POST["myPassword"];

     $pdo = new PDO('mysql:host=192.168.64.2;db=lab10', 'lab10', 'lab10');

     $queryString = "INSERT INTO 'users' ('username', 'password') VALUES ('".$userName."','".$password."')";

     $result = $pdo->prepare($queryString);
     $result->execute();
?>