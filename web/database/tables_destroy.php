<?php
	// Connect to the database and declare the table name
	include_once 'db_connect.php';

	// Delete Table With Post
	if ($_GET["confirm"]=="y")
	{
		// Delete the table
		$sql = "DELETE FROM tbl_cabinet";

		// Check if the table creation was successful, and display an appropriate message
		if ($conn->query($sql) === TRUE) {
			echo "<br>Table ".$tblName." cleared successfully";
		} else {
			echo "Error clearing table: " . $conn->error;
		}
	}
	else
	{
		// Form to Delete
		echo "<form id='confirm'><button type='submit' name='confirm' value='y'>Confirm</button></form>";
	}

	// Close the connection
	$conn->close();
