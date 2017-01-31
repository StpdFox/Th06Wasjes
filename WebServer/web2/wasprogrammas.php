<?php
	$wasprogNameEdit = $_POST["wnameEdit"];
	$wasprogTempEdit = $_POST["tempEdit"];
	$wasprogRPMEdit = $_POST["rpmEdit"];


	//knop edit alles naar string

?>

<html>

	<head>
		<title>Userinterface Wasmachine</title>
		<meta charset=utf-8>
		<meta name="description" content="Wasmachine userinterface">
		<meta name="author" content="Marianne Delmaar, Hendrik Cornelisse, Matthijs Vos">
		<link href="main.css" rel="stylesheet" type="text/css">
	</head>
	
	<body>
	
		<img id=banner src="images/wasmachine.jpg" alt="Banner">
	
		<div id=nav>
			<ul>
				<li><a href="index.html">Home</a></li>
				<li><a href="inloggen.html">Inloggen</a></li>
				<li><a href="wasprogrammas.html"class="selected">Wasprogramma's</a></li>
				<li><a href="loggegevens.html">Loggegevens</a></li>
				<li><a href="contact.html">Contact</a></li>
			</ul>
		</div>		
		<div id=title>
			<h1>Wasprogramma's</h1>
		</div>
		
		<div id=content>
			
			<form name ="wasprogChoose" method="POST" align="left">
			<p><b>Wasprogramma starten</b></p>
					<label>Naam:</label>
					<select id="selectWashprog">
						<option value = "katoen">Katoen</option> <!--waarden temp/rpm meegeven zodat die in de velden worden weergegeven en worden aangepast-->
						<option value = "wol">Wol</option>
						<option value = "kort">Kort</option>
					</select>
					</br>
					<label>Naam:</label>
					<input name="wname" type="text" value="selectWashprog.selected.name"/></br>
					<label>Temp:</label>
					<input name="temp" type="number" min="20" max="90" step="10" value="selectWashprog.selected.temp"/></br>
					<label>RPM:</label>
					<input name="rpm" type="number" min="900" max="1600" step="100" value="selectWashprog.selected.rpm"/>
					</br>
					<input type="checkbox" name="extrawtrlvl" value="Extra spoelen"><label>Extra spoelen</label>
					<p id="buttons">
					<input type="submit" value="Start"/>
					</p>
			</form>
			
			
			<form name ="wasprogEdit" method="GET" align="right" action="<?php $_PHP_SELF ?>">
			<p><b>Wasprogramma toevoegen</b></p>
					<label>Naam:</label>
					<input name="wnameEdit" type="text"/></br>
					<label>Temp:</label>
					<input name="tempEdit" type="number" min="20" max="90" step="10" value="30"/></br>
					<label>RPM:</label>
					<input name="rpmEdit" type="number" min="900" max="1600" step="100" value="1400"/>
					<p id="buttons">
					<input type="submit" value="Opslaan"/>
					</p>
			</form>

		</div>
		
	</body>
	
</html>