#include "Cabinet.h"
#include <thread>
#include <chrono>
#include <iostream>

#define SERVICE_SLEEP_TIME_MILLISECONDS 1

Cabinet::Cabinet(Postman *postie, Switch *doorSwitch, std::string boxID) :
    postie(postie), doorSwitch(doorSwitch), boxID(boxID)
{

}

Cabinet::~Cabinet()
{
    //dtor
}

void Cabinet::Service()
{
    while(true)
    {
        ServiceIter();

        /* Limit how fast ServiceIter is run, otherwise will deplete the
           battery quicker than it should. */

        std::this_thread::sleep_for(std::chrono::milliseconds(SERVICE_SLEEP_TIME_MILLISECONDS));

    }

}

bool Cabinet::ServiceIter()
{

    doorSwitch->StateCheck();
    if(!doorSwitch->IsPressed())
    {
        return postie->sendEventNotification(boxID, "Open", "Available");
    }
    return false;

}

