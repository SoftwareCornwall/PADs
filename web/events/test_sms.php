<?php
  // Include the sms file
  require 'sms.php';
  require '../database/db_connect.php';

  // Declare data to be sent - This would already be defined by the push
  $cabinet_id = "AA123";
  $cabinet_location = "Redruth";

  // Get the numbers from the cabinet
  $phone_numbers = array();

  // Unsafe SQL
  $result = mysqli_query($conn,"SELECT * FROM tbl_guardians WHERE cabinet_id='".$cabinet_id."'");
  while ($row = mysqli_fetch_array($result)) {
      array_push($phone_numbers, $row['phone_number']);
  }

  // Send the messages
  //send_sms($cabinet_id, $cabinet_location, $phone_numbers);

  print_r($phone_numbers);
