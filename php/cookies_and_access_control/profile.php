
<?php
     session_start();//Start the session 
     //We check if the session varialbe named loggedIn excists or if it's value is
     //diffrent than true. In other words we check if the user has valid login 
     //informaiton. If the variable is not set or is not true, we take the user to
     //the login form.
     if(!isset($_SESSION["loggedIn"])|| ($_SESSION["loggedIn"]!= True))
          header("Location: form.html");
?>
<html>
<head>
     <title>Profile Page</title>
</head> 
<body>
     <p>Hello World</p>
</body>
</html>