<html>
<body>
New PAD Location: <?php echo $_POST["pad_l"]; ?><br>
New PAD Postcode:  <?php echo $_POST["pad_id"]; ?>
<br><br>

</body>
</html>
 
<?php
include_once '../database/db_connect.php';

$sql = "";

	 
	// Insert new row with fake details
	$sql .= "INSERT INTO tbl_cabinets (location, postcode)
	VALUES ('".$_POST["pad_l"]."','".$_POST["pad_id"]."');";
	//echo "$sql";
	

	// Check if it was successful
	if ($res=mysqli_multi_query($conn, $sql)) {
		//echo "Successful. ";
	} else {
		// If there was an error, display a message at the top of the page
		echo "New entries could not be added because of an error " . mysqli_error($conn);
	}

$conn->close();
?> 
<html>
<meta http-equiv="refresh" content="0;URL=../../event/abc" />
</html>
