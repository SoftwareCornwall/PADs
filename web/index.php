<?php
require 'vendor/autoload.php';
$app = new \Slim\App();

// Define app routes
$app->post('/event/', function ($request, $response) {
    $data = $request->getParsedBody()['cabinet_id'];
    return $response->write($data);
});

// Run app
$app->run();