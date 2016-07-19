<?php
	// Connect to the database
	include_once 'db_connect.php';
	$errors_occurred = 0;

	// Define cabinets table
	$sql = "CREATE TABLE tbl_cabinets (
		id VARCHAR(200) NOT NULL PRIMARY KEY,
		location VARCHAR(200) NOT NULL,
		postcode VARCHAR(200) NOT NULL
	)";

	// Create cabinets table
	if ($conn->multi_query($sql) === TRUE) {
		echo "<p>Cabinets table created successfully.</p>";
	} else {
		echo "<p>Cabinets table creation failed.</br>";
		echo "Error: " . $conn->error . "</p>";
		$errors_occurred = 1;
	}

	// Define status table
	$sql = "CREATE TABLE tbl_status (
		id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
		cabinet_id VARCHAR(200) NOT NULL,
		door_status VARCHAR(200) NOT NULL,
		defib_status VARCHAR(200) NOT NULL,
		last_update TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
	)";

	// Create status table
	if ($conn->multi_query($sql) === TRUE) {
		echo "<p>Status table created successfully.</p>";
	} else {
		echo "<p>Status table creation failed.</br>";
		echo "Error: " . $conn->error . "</p>";
		$errors_occurred = 1;
	}

	// Define guardians table
	$sql = "CREATE TABLE tbl_guardians (
		id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
		first_name VARCHAR(200) NOT NULL,
		last_name VARCHAR(200) NOT NULL,
		phone_number VARCHAR(200) NOT NULL,
		cabinet_id VARCHAR(200) NOT NULL
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


	//Create GetAllCabinetRecords stored procedure
	$sql = "CREATE PROCEDURE GetAllCabinetRecords()\n"
	."BEGIN\n"
	."SELECT * FROM tbl_cabinets;\n"
	."END";
	if (mysqli_query($conn, $sql)) {
		echo "<p>Created GetAllCabinetRecords stored procedure successfully.</p>";
	} else {
		echo "<p>Error creating stored procedure GetAllCabinetRecords: " . mysqli_error($conn) . "</p>";
	}

	//Create GetCabinetRecord stored procedure
	$sql = "CREATE PROCEDURE GetCabinetRecord(IN cabID VARCHAR(200))\n"
	."BEGIN\n"
	."SELECT * FROM tbl_cabinets WHERE id = cabID;\n"
	."END";
	if (mysqli_query($conn, $sql)) {
		echo "<p>Created GetCabinetRecord stored procedure successfully.</p>";
	} else {
		echo "<p>Error creating stored procedure GetCabinetRecord: " . mysqli_error($conn) . "</p>";
	}

	//Create UpdateCabinetDetails stored procedures
	$sql = "CREATE PROCEDURE `UpdateCabinetDetails`(IN `cabID` VARCHAR(200), IN `NewLocation` VARCHAR(30), IN `NewPostcode` VARCHAR(30)) NOT DETERMINISTIC NO SQL SQL SECURITY DEFINER BEGIN \n"
    . "UPDATE tbl_cabinets \n"
    . "SET tbl_cabinets.location = NewLocation, \n"
    . "tbl_cabinets.postcode = NewPostcode \n"
    . "WHERE tbl_cabinets.id = cabID; \n"
    . "END";
	if (mysqli_query($conn, $sql)) {
		echo "<p>Created UpdateCabinetDetails stored procedure successfully.</p>";
	} else {
		echo "<p>Error creating stored procedure UpdateCabinetDetails: " . mysqli_error($conn) . "</p>";
	}

	// Close the connection
	$conn->close();
?>
