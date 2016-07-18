<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
  <title>Cabinet Event</title>
</head>

<body>
  <?php
    // Connect to the database
    include_once ('../database/db_connect.php');

    // JSON Post Method
    $data = file_get_contents("php://input");
    $data = json_decode($data, true);

    // If data was posted, add it to the status table
    if(!empty($data['cabinet_id']) && !empty($data['door_status']) && !empty($data['defib_status']))
    {
      $cabinet_id = $data['cabinet_id'];
      $door_status = $data['door_status'];
      $defib_status = $data['defib_status'];

      // Update server
      $sql = "INSERT INTO tbl_status (cabinet_id, door_status, defib_status)
      VALUES ('".$cabinet_id."', '".$door_status."', '".$defib_status."')";

      // Check if it was successful
      if ($res=mysqli_query($conn, $sql)) {
        echo "Updated cabinet status.";
      } else {
        echo "Error: " . mysqli_error($conn);
      }
    } else {
      // Echo's a message if there is no data
      echo "No JSON post data.</br>";
    }

    // Close the database connection
    mysqli_close($conn);
  ?>
</body>
</html>
