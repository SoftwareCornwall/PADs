<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
  <title>Cabinet Event</title>
</head>

<body>
  <p>Cabinet request revieved.</p>

  <p>
    <?php
      // JSON Post Method
      $rest_json = file_get_contents("php://input");
      if(isset($rest_json['status']) && !empty($rest_json['status']))
      {
        // Echo's the current value of 'status'.
        echo "JSON Post: ".$rest_json['status']."</br>";
      } else {
        // Echo's a message if there is no data
        echo "No JSON post data.</br>";
      }

      // Standard Post Method
      if(isset($_POST['status']) && !empty($_POST['status']))
      {
        // Echo's the current value of 'status'.
        echo "Standard Post: ".$_POST['status']."</br>";
      } else {
        // Echo's a message if there is no data
        echo "No standard POST data.</br>";
      }
    ?>
  </p>

  <!-- Form to test current post. -->
  <form action="./" method="post">
    <!-- Label -->
    <label for="name">Name:</label>
    <!-- Text field to add name -->
    <input type="text" name="status" id="status" /><p />
    <!-- Submit Button-->
    <input type="submit" name="submit" value="Submit" />
  </form>

</body>
