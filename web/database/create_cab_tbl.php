<?php
	// Connect to the database and declare the table name
	include_once 'db_connect.php';
	$tblName = "tbl_cabinet";

	// Create an SQL table with the set name and three data fields, including the ID, cabinet name and cabinet status
	$sql = "CREATE TABLE ".$tblName." (
		id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
		name VARCHAR(200) NOT NULL,
		status TINYINT(1) NOT NULL 
	)";

	// Check if the table creation was successful, and display an appropriate message
	if ($conn->query($sql) === TRUE) {
		echo "<br>Table ".$tblName." created successfully";
	} else {
		echo "Error creating table: " . $conn->error;
	}

	// Close the connection
	$conn->close();
?>

