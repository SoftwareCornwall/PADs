<?php
	// Database Details
	$servername = "localhost";
	$username = "root";
	$password = "password";
	$dbName = "pads_db";

	// Create aconnection using these variables
	$conn = mysqli_connect($servername, $username, $password, $dbName);

	// Check that the connection was successful
	if (!$conn) {
		// If the connection was not successful, echo a connection error and stop the PHP scripts
		die("Connection failed: " . mysqli_connect_error());
	}
	else
	{
		echo"Connected successfully.";
	}
?>
