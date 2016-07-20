<?php
// Connect to the database
include_once ('../database/db_connect.php');

// JSON Post Method
$data = file_get_contents("php://input");
$data = json_decode($data, true);

// If data was posted, add it to the status table
if(!empty($data['cabinet_id']) && !empty($data['door_status']) && !empty($data['defib_status'])) {
  // Assign the posted variables
  $cabinet_id = mysqli_real_escape_string($conn, $data['cabinet_id']);
  $door_status = mysqli_real_escape_string($conn, $data['door_status']);
  $defib_status = mysqli_real_escape_string($conn, $data['defib_status']);

  // Prepare and bind the statement
  $stmt = $conn->prepare("INSERT INTO tbl_status (cabinet_id, door_status, defib_status) VALUES (?, ?, ?)");
  $stmt->bind_param("sss", $cabinet_id, $door_status, $defib_status);
  $stmt->execute();
  $stmt->close();
  echo "Status update completed.";

  // If the door is open, send the SMS message
  if ($door_status == "Open") {
    include 'door_open.php';
  }
} else {
    echo "No JSON post data.";
}

// Close the database connection
$conn->close();
