<?php

    $servername = "localhost";
    $username = "root";
    $password = "rootth06";
    $dbname = "th06";

    $mysqli = new mysqli($servername, $username, $password, $dbname);

    if($mysqli->connect_errno){
    	echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
    }


    // // Create connection
    // $conn =  mysqli_connect($servername, $username, $password, $dbname);

    // // Check connection
    // if (!$conn) {
    //     die("Connection failed: " .$conn->connect_error);
    // }

    $myusername = $_POST['ID'];
    $mypassword = $_POST['pass'];

    if($myusername == ""){
      	echo '<script language="javascript">';
      	echo 'alert("Enter ID")';
      	echo '</script>';
    }
    elseif ($mypassword == "") {
	    echo '<script language="javascript">';
    	echo 'alert("Enter password")';
    	echo '</script>';
    }
    else{

      $myusername = stripslashes($user_id);
      $mypassword = stripslashes ($user_pass);

      $query = "SELECT * FROM user WHERE user_id ='$myusername' AND user_pass ='$mypassword'";
      $result = mysql_query($conn, $query);
      $count = mysql_num_rows($result);

      if($count==1){
       session_register("myusername");
      session_register("mypassword"); 
      header("location: localhost/Th06/wasprogrammas.html");
      die();
      }
      else{
      }
      //close connection
     //mysql_close($conn);
    }

?>

<html>

	<head>
		<title>Userinterface Wasmachine</title>
		<meta charset=utf-8>
		<meta name="description" content="Wasmachine userinterface">
		<meta name="author" content="Marianne Delmaar, Hendrik Cornelisse, Matthijs Vos">
		<link href="main.css" rel="stylesheet" type="text/css">
		<script type="text/javascript" src="wasmachine.js">	</script>
	</head>
	
	<body>
	
		<img id = "banner" src= "images/wasmachine.jpg" alt="Banner">
	
		<div id = nav>
			<ul>
				<li><a href="index.html">Home</a></li>
				<li><a href="inloggen.html"class="selected">Inloggen</a></li>
				<li><a href="wasprogrammas.html">Wasprogramma's</a></li>
				<li><a href="loggegevens.html">Loggegevens</a></li>
				<li><a href="contact.html">Contact</a></li>
			</ul>
		</div>			
		<div id=title>
			<h1>Inloggen</h1>
		</div>
	

		<div id=contentInlog>
			<p id=ingelogd></p>
			<div id=login class="loggingIn">
				<form name ="inloggen" method="POST" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
					<label>WasmachineID:</label>
					<input name="ID" type="text" size="30"/>
					<label>Wachtwoord:</label>
					<input name="pass" type="password" size="30"/>
					<p id="buttons">
					<input type="submit" value="Login"/>
					</p>
				</form>
			</div>
		</div>
		<div class="container">

</div>

		
	</body>
	
</html>