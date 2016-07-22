<?php
  /* This sends a message and array of phone numbers to the send_sms function.
   * The message body of the SMS can be changed on line 32. */

  if ($old_defib_removed == 0 && $defib_removed == 1) {
    // Include the sms file
    //require_once 'send_sms.php';

    // Get the phone number array for FLEET
    $phone_numbers = array();
    $result = mysqli_query($conn,"SELECT * FROM tbl_fleet");
    while ($row = mysqli_fetch_array($result)) {
      array_push($phone_numbers, $row['phone_number']);
    }

    // Get the cabinet location
    $cabinet_location = "";
    $result = mysqli_query($conn,"SELECT * FROM tbl_cabinets WHERE id='".$cabinet_id."'");
    while ($row = mysqli_fetch_array($result)) {
      $cabinet_location = $row['location'];
    }

    // Prepare the message
    $message = "Defibrillator removed from cabinet ".$cabinet_id." in ".$cabinet_location.".";

    // Send the message
    if (!empty($phone_numbers)) {
      send_sms($message, $phone_numbers);
    }
  }
