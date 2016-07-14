<?php 
require 'vendor/autoload.php';
$app = new \Slim\App();


$app->get('/hello/{name}', function($request, $response, $args) {
	return $response->write("Hello ".$args['name']);
});

$app->get('/bye/{name}', function($request, $response, $args) {
	return $response->write("Bye ".$args['name']);
});

$app->post('/event', function ($request, $response, $args) {
	$data = $request->getParsedBody(); //creates array from data posted by user
	return $response->write($data["abc"]);
});

// Get container
$container = $app->getContainer();

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
    return $this->view->render($response, 'sample.html', [
        'id' => $args['id'] ]);

});
$app->run();


