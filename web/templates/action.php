<html>
<body>
New PAD Location: <?php echo $_POST["pad_l"]; ?><br>
New PAD Postcode:  <?php echo $_POST["pad_id"]; ?><br>
New PAD Postcode:  <?php echo $_POST["pad_post"]; ?><br>
New PAD Postcode:  <?php echo $_POST["pad_door"]; ?><br>
New PAD Postcode:  <?php echo $_POST["pad_defib"]; ?>
<br><br>

</body>
</html>
 
<?php
include_once '../database/db_connect.php';

$sql = "";

	 
	// Insert new row with fake details
	$sql .= "INSERT INTO tbl_cabinets (id, location, postcode)
	VALUES ('".$_POST["pad_id"]."','".$_POST["pad_l"].",'".$_POST["pad_post"]."');";
	//echo "$sql";
	

	// Check if it was successful
	if ($res=mysqli_multi_query($conn, $sql)) {
		//echo "Successful. ";
	} else {
		// If there was an error, display a message at the top of the page
		echo "New entries could not be added because of an error " . mysqli_error($conn);
	}

/*,'".$_POST["pad_door"].",'".$_POST["pad_defib"]."'
	// Insert new row with fake details
	$sql .= "INSERT INTO tbl_status (cabinet_id, postcode)
	VALUES ('".$_POST["pad_id"]."','".$_POST["pad_l"].",'".$_POST["pad_post"]."');";
	//echo "$sql";*/
	//
//REWRITE FOR STATUS TABLE, LAST 2 VALUES

	/* Check if it was successful
	if ($res=mysqli_multi_query($conn, $sql)) {
		//echo "Successful. ";
	} else {
		// If there was an error, display a message at the top of the page
		echo "New entries could not be added because of an error " . mysqli_error($conn);
	}
*/

$conn->close();
?> 
<html>
<meta http-equiv="refresh" content="0;URL=../../event/abc" />
</html>
