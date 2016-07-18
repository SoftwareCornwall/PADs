<?php
use PHPUnit/Framework/TestCase;
include ('../webtest.php');

// Test MySQL CRUD outputs
class DBTest extends TestCase
{
    //Assert that cabinet door status update executes and has saved the correct value
    public function test1()
    {
        // Assert
        $this->assertEquals("test", testFunction());

    }

    //Assert that cabinet status beep update executes and has saved the correct value


}
