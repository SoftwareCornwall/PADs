<?php
	// Connect to the database
	include_once 'db_connect.php';
	$errors_occurred = 0;

	// Define cabinets table
	$sql = "CREATE TABLE tbl_cabinets (
		id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
		location VARCHAR(200) NOT NULL,
		postcode VARCHAR(200) NOT NULL,
		door_status VARCHAR(200) NOT NULL,
		defig_status VARCHAR(200) NOT NULL,
		last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
	)";

	// Create cabinets table
	if ($conn->multi_query($sql) === TRUE) {
		echo "<p>Cabinets table created successfully.</p>";
	} else {
		echo "<p>Cabinets table creation failed.</br>";
		echo "Error: " . $conn->error . "</p>";
		$errors_occurred = 1;
	}

	// Define guardians table
	$sql = "CREATE TABLE tbl_guardians (
		id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
		first_name VARCHAR(200) NOT NULL,
		last_name VARCHAR(200) NOT NULL,
		phone_number VARCHAR(200) NOT NULL,
		cabinet_id INT NOT NULL
	)";

	// Create guardians table
	if ($conn->multi_query($sql) === TRUE) {
		echo "<p>Guardians table created successfully.</p>";
	} else {
		echo "<p>Guardians table creation failed.</br>";
		echo "Error: " . $conn->error . "</p>";
		$errors_occurred = 1;
	}

	// If errors occurred
	if ($errors_occurred == 1) {
		echo "<p>One or more of the tables could not be created.</br>";
		echo "Please ensure that you have created the database first.</p>";
	}

	// Close the connection
	$conn->close();

