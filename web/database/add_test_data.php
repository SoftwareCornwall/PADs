<?php
	// Connect to the database and set table name
	include_once ('dbconnect.php');
	$tblName = "tbl_cabinet";
	$sql = "";

	for ($count = 0; $count < 150; $count++) {
		// Insert new row with fake details
		$name = "Cab".$count;
		$sql .= "INSERT INTO ".$tblName." (name, status)
		VALUES ('".$name."', 1);";
	}

	// Check if it was successful
	if ($res=mysqli_multi_query($conn, $sql)) {
		echo "Added 150 fake entries.";
	} else {
		// If there was an error, display a message at the top of the page
		echo "Fake entries could not be added due to an error. </br> Error: " . mysqli_error($conn);
	}

	mysqli_close($conn);
?>
