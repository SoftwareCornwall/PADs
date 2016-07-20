<?php
// Connect to the database
include_once ('../database/db_connect.php');

// JSON Post Method
$data = file_get_contents("php://input");
$data = json_decode($data, true);

// If data was posted, add it to the status table
if(!empty($data['cabinet_id']) && !empty($data['door_status']) && !empty($data['defib_status'])) {
  // Declare the posted variables
  $cabinet_id = mysqli_real_escape_string($conn, $data['cabinet_id']);
  $door_status = mysqli_real_escape_string($conn, $data['door_status']);
  $defib_status = mysqli_real_escape_string($conn, $data['defib_status']);

  // Declare the variables for the old status
  $old_door_status = "";
  $old_defib_status = "";

  // Get the old status data from the status table
  $sql = "SELECT * FROM tbl_status WHERE cabinet_id='".$cabinet_id."' ORDER BY last_update DESC LIMIT 1;";
  $result = mysqli_query($conn, $sql);
  while($row = mysqli_fetch_assoc($result)) {
    $old_door_status = $row['door_status'];
    $old_defib_status = $row['defib_status'];
  }

  // Add a new status entry
  $sql = "INSERT INTO tbl_status (cabinet_id, door_status, defib_status)
          VALUES ('".$cabinet_id."', '".$door_status."', '".$defib_status."')";

  if (mysqli_query($conn, $sql)) {
    echo "<p>Status update complete.<p>";
  } else {
    echo "<p>Error: " . $sql . "<br>" . mysqli_error($conn) . "</p>";
  }

  // If the door is open, send the SMS message
  if ($old_door_status == "Closed" && $door_status == "Open") {
    include 'door_open.php';
  }
} else {
    echo "No post data recieved.";
}

// Close the database connection
$conn->close();
