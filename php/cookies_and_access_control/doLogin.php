<?php
     session_start(); // Start the session autogenerating a session ID cookie
     //Gather user information from the html form.
     $userName = $_POST["uName"];
     $password = $_POST["myPassword"];

     //The followin function will validate the user information from the login form
     //either connecting to a mySQL database or from a text File.
     //This function return true if a user name is found with a matching password and
     //False if not. 

     /*
     $validUser = validateUserInfo($userName, $password);
     if($validUser === True)
     {
          //If the user is found and the password is correct, we create a session
          //varialbe named $loggedIn and set it to true. We will use this variable
          //for access control to other pages.
          //After we set the variable to true, we take the user to their profile page  
          $_SESSION["loggedIn"] = True;
          header("Location: profile.php");
     }
          else
     {
          //If the user name is not found or the password does not match we take the
          //user back to the login page.
          header("Location: form.html");
     }
     */

     $pdo = new PDO('mysql:host=192.168.64.2;db=lab10', 'lab10', 'lab10');
     $queryString = "SELECT * FROM users WHERE username = '".$userName."'";

     $result = $pdo->prepare($queryString);
     $result->execute();
     $validUser = False;

     for ($i=0; $row = $result->fetch(); $i++) {
          if ($row['password'] === $password) {
               $validUser = True;
          }
     }

     if ($validUser === True) {
          $_SESSION["loggedIn"] = True;
          header("Location: profile.php");
     } else {
          header("Location: loginForm.html");
     }

?>
