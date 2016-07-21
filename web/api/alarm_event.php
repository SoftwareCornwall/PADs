<?php

/**
This code relies on the FLEET staff table, which does not currently exist.
Including this file will result in errors.
**/

if ($old_alarm_status == "Working" && $alarm_status == "Fault") {
  // Include the sms file
  require 'send_sms.php';

  // Get the phone number array
  $phone_numbers = array();
  $result = mysqli_query($conn,"SELECT 'phone_numbers' FROM tbl_fleet_staff");
  while ($row = mysqli_fetch_array($result)) {
    array_push($phone_numbers, $row['phone_number']);
  }

  // Prepare the message
  $message = "The defibrillator in cabinet ".$cabinet_id." at ".$cabinet_location." is reporting a fault.";

  // Send the message
  send_sms($message, $phone_numbers);
}
