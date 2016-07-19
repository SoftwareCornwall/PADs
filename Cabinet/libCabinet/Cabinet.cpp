#include "Cabinet.h"
#include <iostream>

Cabinet::Cabinet(Postman *postie, std::string boxID) :
    postie(postie), boxID(boxID)
{

}

Cabinet::~Cabinet()
{
    //dtor
}

bool Cabinet::DoorEventCallback(bool doorOpen)
{

    if(doorOpen)
    {
        return postie->SendEventNotification(boxID, "Open", "Available");
    }
    return false;

}

