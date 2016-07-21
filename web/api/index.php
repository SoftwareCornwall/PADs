<?php
  // Connect to the database
  include_once ('../database/db_connect.php');

  // JSON Post Method
  $data = file_get_contents("php://input");
  $data = json_decode($data, true);

  // Declare variables

  // If data was posted, add it to the status table
  if (!empty($data['cabinet_id']) && !empty($data['door_status']) &&
      !empty($data['hanger_status']) && !empty($data['alarm_status']) &&
      !empty($data['temp_status'])) {

    // Get and echo the post data
    $cabinet_id = mysqli_real_escape_string($conn, $data['cabinet_id']);
    $door_status = mysqli_real_escape_string($conn, $data['door_status']);
    $hanger_status = mysqli_real_escape_string($conn, $data['hanger_status']);
    $alarm_status = mysqli_real_escape_string($conn, $data['alarm_status']);
    $temp_status = mysqli_real_escape_string($conn, $data['temp_status']);

    echo "<p>Cabinet ID: ".$cabinet_id;
    echo "<br>Door Status: ".$door_status;
    echo "<br>Hanger Status: ".$hanger_status;
    echo "<br>Alarm Status: ".$alarm_status;
    echo "<br>Temp Status: ".$temp_status."&#176;C</p>";

    // Declare and set the old status variables
    $old_door_status = "";
    $old_alarm_status = "";

    $sql = "SELECT * FROM tbl_status WHERE cabinet_id='".$cabinet_id."'
            ORDER BY last_update DESC LIMIT 1;";
    $result = mysqli_query($conn, $sql);
    while($row = mysqli_fetch_assoc($result)) {
      $old_door_status = $row['door_status'];
      $old_alarm_status = $row['alarm_status'];
    }

    // Update the status table with the new entries
    $sql = "INSERT INTO tbl_status (cabinet_id, door_status, hanger_status, alarm_status, temp_status)
            VALUES ('".$cabinet_id."', '".$door_status."', '".$hanger_status."', '".$alarm_status."', '".$temp_status."')";
    if (mysqli_query($conn, $sql)) {
      echo "<p>Status update complete.<p>";
    } else {
      echo "<p>Error: " . $sql . "<br>" . mysqli_error($conn) . "</p>";
    }

    // Run SMS events

    include 'door_event.php';
  } else {
      echo "No post data recieved.";
  }

  // Close the database connection
  $conn->close();
