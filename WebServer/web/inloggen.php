<?php
/*	$user = $_POST['ID'];
	$password = $_POST['ww'];
	$database = new SQLite3('wasmachine.db');
	
	$stmt = $database->prepare('SELECT gebruiker, wachtwoord FROM account WHERE gebruiker = :user');
	$stmt->bindValue(':user', $user, SQLITE3_TEXT);

	$result = $stmt->execute();
	$array = $result->fetchArray();
	
	if($array && $password == $array['wachtwoord']){
		session_start();
	}
	*/
	
?>
	
<?php
    $dir = 'C:/Users/Mier/Dropbox/Wasmachines leven langer met ons/wasmachine.db';
    $dbh = new PDO($dir) or die ("cannot open");

    $myusername = $_POST['ID'];
    $mypassword = $_POST['ww'];

    $myusername = stripslashes($myusername);
    $mypassword = stripslashes ($mypassword);

    $query = "SELECT * FROM account WHERE gebruiker ='$myusername' AND wachtwoord ='$mypassword'";
    $result = mysql_query($query);
    $count = mysql_num_rows($result);

    if($count==1){
    echo'worked';
    }

?>