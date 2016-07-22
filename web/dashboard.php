<?php

	use \Psr\Http\Message\ServerRequestInterface as Request;	//shortens path to 'request'
	use \Psr\Http\Message\ResponseInterface as Response;	//^^to 'Response'
	require 'vendor/autoload.php';
	$app = new \Slim\App();

	$app->post('/event', function ($request, $response, $args) {
		$data = $request->getParsedBody(); 	//creates array from data posted by user
		return $response->write($data["id"]);
});

	$config['displayErrorDetails'] = true;
	$config['addContentLengthHeader'] = false;

	$config['db']['host']   = "localhost";
	$config['db']['user']   = "root";
	$config['db']['pass']   = "password";
	$config['db']['dbname'] = "pads_db";		//login to database

	$app = new \Slim\App(["settings" => $config]);

	// Get container
	$container = $app->getContainer();

	// Assign variables holding the server details required to connect
	$servername = "localhost";
	$username = "root";
	$password = "password";
	$dbName = "pads_db";
	$portNumber = "3306";

	// Create aconnection using these variables
	$conn = mysqli_connect($servername, $username, $password, $dbName, $portNumber);

	// Check that the connection was successful
	if (!$conn) {
		// If the connection was not successful, echo a connection error and stop the PHP scripts
		die("Connection failed: " . mysqli_connect_error());
}


		//Register component on container
	$container['view'] = function ($container) {
    	$view = new \Slim\Views\Twig('./templates', [
		//'cache' => 'home/pi/PADs/web/cache'
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

	$conn= mysqli_connect("localhost", "root", "password", "pads_db", "3306")//creates connection!>
				or die ("Sorry -  could not connect to MySQL");

	$query = "SELECT cabs.id, cabs.location, cabs.postcode, SUBTIME(CURRENT_TIMESTAMP(),'1:02:00') cut_off_time,
		COALESCE(
	   	(SELECT stats.door_open
	    	FROM tbl_status stats
	    	WHERE stats.cabinet_id = cabs.id ORDER BY stats.last_update DESC LIMIT 1) , 'Not available') door_open,
		COALESCE(
	   	(SELECT stats.defib_removed
	    	FROM tbl_status stats
	    	WHERE stats.cabinet_id = cabs.id ORDER BY stats.last_update DESC LIMIT 1) , 'Not available') defib_removed,
		COALESCE(
			(SELECT stats.alarm_status
				FROM tbl_status stats
				WHERE stats.cabinet_id = cabs.id ORDER BY stats.last_update DESC LIMIT 1) , 'Not available') alarm_status,
		COALESCE(
	   	(SELECT stats.last_update
	    	FROM tbl_status stats
	    	WHERE stats.cabinet_id = cabs.id ORDER BY stats.last_update DESC LIMIT 1) , 'Not available') last_update
		FROM tbl_cabinets cabs
		ORDER BY cabs.id ASC";

	$result = mysqli_query($conn, $query); //takes everything from tbl_cabinet, assigns to value $query!>

	$tplArray = array();
	while ( $row = mysqli_fetch_array ( $result ) )
	{
		$door_open = (boolval($row['door_open']) ? 'Open' : 'Closed');

		if ($row ['defib_removed'] == 1)	{
			$defib_status = "Unavailable";
		} elseif ($row ['alarm_status'] == 1) {
			$defib_status = "Fault";
		} else {
			$defib_status = "Available";
		}
		// ------------------------------------------------------------------------
		$tplArray[] = array (
			'id' => $row ['id'],
			'location' => $row ['location'],
			'postcode'=>$row['postcode'],//gets fields from 'select *' to pass to html to display + gives data names
			'door_status'=>$door_open,
			'defib_status'=>$defib_status,
			'last_update'=>$row['last_update'],
			'cut_off_time'=>$row['cut_off_time']
	 	);
	}

    return $this->view->render($response, 'sample.html', //calls sample.html
        array('cabinets' => $tplArray)); //   'id' => $args['id'] ]);
});

$app->run();
