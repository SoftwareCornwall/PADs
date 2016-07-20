#include "Cabinet.h"
#include <iostream>
#include <algorithm>    // std::search

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
        return postie->sendEventNotification(boxID, "Open", "Down");
    }
    return false;

}

bool Cabinet::HangerEventCallback(bool hangerDown)
{

    if(hangerDown)
    {
        return postie->sendEventNotification(boxID, "Open", "Down");
    }
    return false;

}

bool Cabinet::IsSubstringPresentInOutputString(std::string subStr, std::string outputStr)
{
    auto foundStart = std::search(outputStr.begin(), outputStr.end(), subStr.begin(), subStr.end());

    if (foundStart != outputStr.end())
    {
        return true;
    }
    return false;

}

