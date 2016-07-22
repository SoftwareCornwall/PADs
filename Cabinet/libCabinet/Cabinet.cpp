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

    return postie->sendEventNotification(boxID, doorIsOpen, hangerIsDown);

}

bool Cabinet::HangerEventCallback(bool hangerDown)
{
    hangerIsDown = hangerDown;

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





