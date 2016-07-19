<?php
	// Connect to the database and declare the table name
	include_once 'db_connect.php';

	// Delete Table With Post
	if ($_GET["confirm"]=="y")
	{
		// Delete the table
		$sql = "DROP TABLE tbl_cabinets";

		// Check if the table creation was successful, and display an appropriate message
		if ($conn->query($sql) === TRUE) {
			echo "</p>Cabinets table cleared successfully</p>";
		} else {
			echo "</p>Error clearing table: " . $conn->error . "</p>";
		}

		// Delete the table
		$sql = "DROP TABLE tbl_status";

		// Check if the table creation was successful, and display an appropriate message
		if ($conn->query($sql) === TRUE) {
			echo "</p>Status table cleared successfully.</p>";
		} else {
			echo "</p>Error clearing table: " . $conn->error . "</p>";
		}

		// Delete the table
		$sql = "DROP TABLE tbl_guardians";

		// Check if the table creation was successful, and display an appropriate message
		if ($conn->query($sql) === TRUE) {
			echo "</p>Guardians table cleared successfully.</p>";
		} else {
			echo "</p>Error clearing table: " . $conn->error . "</p>";
		}
	}
	else
	{
		// Form to Delete
		echo "<form id='confirm'><button type='submit' name='confirm' value='y'>Confirm</button></form>";
	}

	// Close the connection
	$conn->close();
