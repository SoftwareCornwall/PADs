<html>
<body>
Welcome <?php echo $_POST["pad_l"]; ?><br>
Your email address is: <?php echo $_POST["pad_id"]; ?>


</body>
</html>
 
<?php
include_once '../database/db_connect.php';

$sql = "";

	 
	// Insert new row with fake details
	$sql .= "INSERT INTO tbl_cabinets (location, postcode)
	VALUES ('".$_POST["pad_l"]."','".$_POST["pad_id"]."');";
	echo "echo statement:"."$sql";
	

	// Check if it was successful
	if ($res=mysqli_multi_query($conn, $sql)) {
		echo "Successful.";
	} else {
		// If there was an error, display a message at the top of the page
		echo "Fake entries could not be added due to an error. </br> Error: " . mysqli_error($conn);
	}


echo "Hello world!<br>";
$conn->close();
?> 


