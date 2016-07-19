<?php
  // Include the sms file
  require 'sms.php';

  // Declare data to be sent
  $cabinet_id = "AA123";
  $cabinet_location = "Redruth";
  $phone_numbers = array();
  array_push($phone_numbers, "+447597997201");

  // Send the messages
  send_sms($cabinet_id, $cabinet_location, $phone_numbers);
