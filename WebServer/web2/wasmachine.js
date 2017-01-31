function loggedIn(){	
	var ID = document.forms["inloggen"]["ID"].value;
	var ww = document.forms["inloggen"]["ww"].value;

	if (ID == null || ID == ""){
		alert("vul ID in");
		return false;
	}
	if (ww == null || ww == ""){
		alert("vul wachtwoord in");
		return false;
	}
	else{
		klaar();
		return false;
	}
}

function klaar(){
	document.getElementById("login").style.display = "none";
	document.getElementById("ingelogd").style.display = "block";
	document.getElementById("ingelogd").innerHTML = "Welkom, " + getID() + "!";
}

function getID(){
	return document.forms["inloggen"]["ID"].value;
}

