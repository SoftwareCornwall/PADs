<?php
  /* API Reference:
   * cabinet_id
   * door_open (0 = Closed / 1 = Open)
   * defib_removed (0 = In Cabinet / 1 = Removed)
   * alarm_status (0 = Working / 1 = Fault)
   * temp_status (int value of current temperature)*/

  // Add dbconnect and Twilio
  include_once ('../database/db_connect.php');
  require 'send_sms.php';

  // JSON Post Method
  $data = file_get_contents("php://input");
  $data = json_decode($data, true);

  // If data was posted, add it to the status table
  if (!empty($data['cabinet_id']) && !empty($data['temp_status'])) {

    // Get and echo the post data
    $cabinet_id = mysqli_real_escape_string($conn, $data['cabinet_id']);
    $door_open = mysqli_real_escape_string($conn, $data['door_open']);
    $defib_removed = mysqli_real_escape_string($conn, $data['defib_removed']);
    $alarm_status = mysqli_real_escape_string($conn, $data['alarm_status']);
    $temp_status = mysqli_real_escape_string($conn, $data['temp_status']);

    echo "<p>Cabinet ID: ".$cabinet_id;
    echo "<br>Door Open: ".(boolval($door_open) ? 'True' : 'False');
    echo "<br>Defib Removed: ".(boolval($defib_removed) ? 'True' : 'False');
    echo "<br>Defib Fault: ".(boolval($alarm_status) ? 'True' : 'False');
    echo "<br>Temp Status: ".$temp_status."°C</p>";

    // Declare and set the old status variables
    $old_door_open = "";
    $old_defib_removed = "";
    $old_alarm_status = "";

    $result = mysqli_query($conn,"SELECT * FROM tbl_status WHERE cabinet_id='".$cabinet_id."'
            ORDER BY last_update DESC LIMIT 1;");
    while ($row = mysqli_fetch_array($result)) {
      $old_door_open = $row['door_open'];
      $old_defib_removed = $row['defib_removed'];
      $old_alarm_status = $row['alarm_status'];
    }

    // Update the status table with the new entries
    $sql = "INSERT INTO tbl_status (cabinet_id, door_open, defib_removed, alarm_status, temp_status)
            VALUES ('".$cabinet_id."', '".$door_open."', '".$defib_removed."', '".$alarm_status."', '".$temp_status."')";
    if (mysqli_query($conn, $sql)) {
      echo "<p>Status update complete.<p>";
    } else {
      echo "<p>Error: " . $sql . "<br>" . mysqli_error($conn) . "</p>";
    }

    // Run SMS events
    include 'door_event.php';
    include 'alarm_event.php';
    include 'defib_event.php';

  } elseif (!empty($data['cabinet_id'])) {
      echo "<p>Missing some JSON post data. The status update could not be completed.</p>";
  } else {
    echo "<p>No cabinet JSON data received.<p>";
  }

  // Close the database connection
  $conn->close();
