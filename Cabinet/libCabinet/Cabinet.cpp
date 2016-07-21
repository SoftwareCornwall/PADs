#include "Cabinet.h"
#include <iostream>
#include <algorithm>    // std::search
#include "CurrentTime.hpp"
#include <chrono>

using namespace ::std::chrono;

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
    doorIsOpen = doorOpen;

   /* if(doorOpen)
    {
        return postie->sendEventNotification(boxID, "Open", "Down");
    }
    return false;

    */

    return postie->sendEventNotification(boxID, doorIsOpen, hangerIsDown);

}

bool Cabinet::HangerEventCallback(bool hangerDown)
{
    hangerIsDown = hangerDown;

    /* if(hangerDown)
    {
        return postie->sendEventNotification(boxID, "Open", "Down");
    }
    else
    {
        return postie->sendEventNotification(boxID, "Open", "Up");
    }
    return false;
    */

    return postie->sendEventNotification(boxID, doorIsOpen, hangerIsDown);

}

void Cabinet::StatusService()
{
    if ((currentTime() - lastMessageSentTime) >= minutes(15))
    {
        lastMessageSentTime = currentTime();
        postie->sendEventNotification(boxID, doorIsOpen, hangerIsDown);
    }

}





