<html>
<body>
Welcome <?php echo $_POST["pad_l"]; ?><br>
Your email address is: <?php echo $_POST["pad_id"]; ?>


</body>
</html>
 
<?php
include_once '../database/db_connect.php';
echo "Hello world!<br>";
$conn->close();
?> 


