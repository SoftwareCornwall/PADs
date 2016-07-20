<?php
require '../vendor/twilio-php-master/Services/Twilio.php';

function send_sms($body, $phone_numbers)
{
  // Username: toylorey@gmail.com
  // Password: !1Password

  $AccountSid = "AC5328ae4509376e99ccfaaceb910e4369"; // Your Account SID from www.twilio.com/console
  $AuthToken = "b4aa6990121bf8b6298d236c899b4c6a";   // Your Auth Token from www.twilio.com/console

  $client = new Services_Twilio($AccountSid, $AuthToken);

  foreach ($phone_numbers as $send_number)
  {
    $message = $client->account->messages->create(array(
      "From" => "+441671642020", // From a valid Twilio number
      "To" => $send_number,   // Text this number
      "Body" => $body,
    ));
  }

  // Display a confirmation message on the screen
  echo "Sent message {$message->sid}";
}
