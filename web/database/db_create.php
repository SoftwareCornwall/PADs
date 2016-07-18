<?php
	// Server Details
	$servername = "localhost";
	$username = "root";
	$password = "password";

	// Create aconnection using these variables
	$conn = mysqli_connect($servername, $username, $password);

	// Check that the connection was successful
	if (!$conn) {
		die("<p>Connection failed: " . mysqli_connect_error()) . "</p>";
	} else {
		echo"<p>Connected successfully.</p>";
	}

  // Create the database
  $sql = "CREATE DATABASE pads_db";
  if (mysqli_query($conn, $sql)) {
    echo "<p>Database created successfully.</p>";
  } else {
    echo "<p>Error creating database: " . mysqli_error($conn) . "</p>";
  }

