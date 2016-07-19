<?php
// Include the sms file
require 'twilio.php';

// Get the phone number array
$phone_numbers = array();
$result = mysqli_query($conn,"SELECT * FROM tbl_guardians WHERE cabinet_id='".$cabinet_id."'");
while ($row = mysqli_fetch_array($result)) {
    array_push($phone_numbers, $row['phone_number']);
}

// Get the cabinet location
$cabinet_location = "";
$result = mysqli_query($conn,"SELECT * FROM tbl_cabinets WHERE id='".$cabinet_id."'");
while ($row = mysqli_fetch_array($result)) {
    $cabinet_location = $row['location'];
}

// Send the message
send_sms($cabinet_id, $cabinet_location, $phone_numbers);
