<?php
  /* This sends a message and array of phone numbers to the send_sms function.
   * The message body of the SMS can be changed on line 30. */

  if ($old_door_open == 0 && $door_open == 1) {
    // Include the sms file
    //require_once 'send_sms.php';

    // Get the phone number array for guardians
    $phone_numbers = array();
    $result = mysqli_query($conn,"SELECT * FROM tbl_guardians WHERE cabinet_id='".$cabinet_id."'");
    while ($row = mysqli_fetch_array($result)) {
      array_push($phone_numbers, $row['phone_number']);
    }

    // Get the phone number array for FLEET
    $result = mysqli_query($conn,"SELECT * FROM tbl_fleet");
    while ($row = mysqli_fetch_array($result)) {
      array_push($phone_numbers, $row['phone_number']);
    }

    // Get the cabinet location
    $cabinet_location = "";
    $result = mysqli_query($conn,"SELECT location FROM tbl_cabinets WHERE id='".$cabinet_id."'");
    while ($row = mysqli_fetch_array($result)) {
      $cabinet_location = $row['location'];
    }

    // Prepare the message
    $message = "The cabinet ".$cabinet_id." in ".$cabinet_location." has been opened.";

    // Send the message
    send_sms($message, $phone_numbers);
  }
