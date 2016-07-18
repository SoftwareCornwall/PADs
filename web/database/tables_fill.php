<?php
	// Connect to the database and set table name
	include_once ('db_connect.php');
	$sql = "";

	for ($count = 0; $count < 150; $count++) {
		// Insert new row with fake details
		$sql .= "INSERT INTO tbl_cabinets (location, postcode)
		VALUES ('sample location', 'EX00 0AA');";
	}

	// Check if it was successful
	if ($res=mysqli_multi_query($conn, $sql)) {
		echo "Added 150 fake cabinets.";
	} else {
		// If there was an error, display a message at the top of the page
		echo "Fake entries could not be added due to an error. </br> Error: " . mysqli_error($conn);
	}

	mysqli_close($conn);
?>
