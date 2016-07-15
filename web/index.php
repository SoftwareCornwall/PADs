<?php 

use \Psr\Http\Message\ServerRequestInterface as Request;//shortens path to 'request'
use \Psr\Http\Message\ResponseInterface as Response;//^^to 'Response'
require 'vendor/autoload.php';
$app = new \Slim\App(); 

$app->post('/event', function ($request, $response, $args) {
	$data = $request->getParsedBody(); //creates array from data posted by user
	return $response->write($data["id"]);
});

$config['displayErrorDetails'] = true;
$config['addContentLengthHeader'] = false;

$config['db']['host']   = "localhost";
$config['db']['user']   = "root";
$config['db']['pass']   = "password";
$config['db']['dbname'] = "pads_db";//login to database

$app = new \Slim\App(["settings" => $config]);



// Get container
$container = $app->getContainer();

	// Assign variables holding the server details required to connect
	$servername = "localhost";
	$username = "root";
	$password = "password";
	$dbName = "pads_db";

	// Create aconnection using these variables
	$conn = mysqli_connect($servername, $username, $password, $dbName);

	// Check that the connection was successful
	if (!$conn) {
		// If the connection was not successful, echo a connection error and stop the PHP scripts
		die("Connection failed: " . mysqli_connect_error());
	}
/*
	}
	else
	{
		echo"Connected successfully.";
	}
*/

	$query = mysqli_query($conn, 'SELECT * FROM tbl_cabinet');

//$rows= mysqli_fetch_array($query)

	while ($row = mysqli_fetch_array($query))
	{
		echo $row['name'];
	
	}

//Register component on container
$container['view'] = function ($container) {
    $view = new \Slim\Views\Twig('./templates', [
//        'cache' => 'home/pi/PADs/web/cache'
        'cache' => false
    ]);

    $view->addExtension(new \Slim\Views\TwigExtension(
        $container['router'],
        $container['request']->getUri()
    ));

    return $view;
};

// Render Twig template in route
$app->get('/event/{id}', function ($request, $response, $args) {
    return $this->view->render($response, 'sample.html', [//calls sample.html
        'id' => $args['id'] ]);
});


$app->run();
//$app = new \Slim\App();



$app->get('/hello/{name}', function($request, $response, $args) {
	return $response->write("Hello ".$args['name']);
});

$app->get('/bye/{name}', function($request, $response, $args) {
	return $response->write("Bye ".$args['name']);
});



?>
