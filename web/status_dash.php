<?php 

use \Psr\Http\Message\ServerRequestInterface as Request;//shortens path to 'request'
use \Psr\Http\Message\ResponseInterface as Response;//^^to 'Response'
require '../vendor/autoload.php';
$app = new \Slim\App(); 

$app->post('/status', function ($request, $response, $args) {
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


$query = mysqli_query($conn, 'SELECT * FROM tbl_status');


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
$app->get('/status/{id}', function ($request, $response, $args) {

	$conn= mysqli_connect("localhost", "root", "password", "pads_db")//creates connection!>
				or die ("Sorry -  could not connect to MySQL");

	$result = mysqli_query($conn, 'SELECT * FROM tbl_status'); //takes everything from tbl_cabinet, assigns to value $query!>

	$tplArray = array(); 
	while ( $row = mysqli_fetch_array ( $result ) )
	{
	    $tplArray[] = array (
		 'cabinet_id' => $row ['cabinet_id'],
		 'door_status' => $row ['door_status'], 
		'defib_status'=>$row['defib_status'],//gets fields from 'select *' to pass to html to display + gives data names
		'last_update'=>$row['last_update']
	    );
	}


    return $this->view->render($response, '/templates/status.html', //calls sample.html
        array('cabinets' => $tplArray)); //   'id' => $args['id'] ]);
});

$app->run();

$app->get('/hello/{name}', function($request, $response, $args) {
	return $response->write("Hello ".$args['name']);
});

$app->get('/bye/{name}', function($request, $response, $args) {
	return $response->write("Bye ".$args['name']);
});

?>
