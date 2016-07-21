<html>
<body>
<!--New PAD ID:  <?php echo $_POST["pad_id"]; ?><br>
New PAD Location: <?php echo $_POST["pad_l"]; ?><br>
New PAD Postcode:  <?php echo $_POST["pad_post"]; ?><br>
New PAD Door Status:  <?php echo $_POST["pad_door"]; ?><br>
New PAD Defib Status:  <?php echo $_POST["pad_defib"]; ?>-->
<br><br>

</body>
</html>
 
<?php
include_once '../database/db_connect.php';

$sql = "";

	 
	// Insert new row with fake details
	//$sql .= "INSERT INTO tbl_cabinets (id, location, postcode) VALUES ("a","b","c");
	$pad_id = $_POST["pad_id"];	
	$pad_l = $_POST["pad_l"];
	$pad_post = $_POST["pad_post"];	
	$cabinet_id = $_POST["pad_id"];	
	$pad_door = $_POST["pad_door"];
	$pad_defib = $_POST["pad_defib"];

	$sql = "INSERT INTO tbl_cabinets (id, location, postcode) VALUES ('$pad_id', '$pad_l', '$pad_post');"; 
	$sql .= "INSERT INTO tbl_status (cabinet_id, door_status, defib_status) VALUES ('$pad_id', '$pad_door', '$pad_defib');";
	

	//add values to tbl_status

	
	//$sql .= "INSERT INTO tbl_status (id, door_status, defib_status) VALUES ('$cabinet_id', '$pad_door', '$pad_defib');";

	/*$sql .= "INSERT INTO tbl_status (id, door_status, defib_status)
	VALUES ('".$_POST["pad_id"]."','".$_POST["pad_door"].",'".$_POST["pad_defib"]."');";*/

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
<meta http-equiv="refresh" content="30;URL=../../event/abc" />
</html>
