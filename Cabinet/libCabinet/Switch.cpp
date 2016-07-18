#include "Switch.hpp"
#include "CurrentTime.hpp"
#include <thread>
#include <chrono>

#define SERVICE_SLEEP_TIME_MILLISECONDS 1

using namespace ::std::chrono;

Switch::Switch(InputPin *switchPin, doorCallback doorEventCallback)
{
    doorCallbackFunction = doorEventCallback;
    pin = switchPin;
    previouslyPressed = false;
    PressedState = false;
}

bool Switch::IsPressed()
{
    return PressedState;
}

void Switch::StateCheck()
{

    if(pin->State() == false)
    {
        PressedState = false;
        previouslyPressed = false;
    }
    else
    {

        if (previouslyPressed == false)
        {
            firstTime = currentTime();

        }
        else
        {
           if ((currentTime() - firstTime) >= milliseconds(10))
           {
                PressedState = true;
                doorCallbackFunction(true);
           }
        }
        previouslyPressed = true;

    }

}

void Switch::Service()
{

    while(true)
    {
        ServiceIter();

        /* Limit how fast ServiceIter is run, otherwise will deplete the
           battery quicker than it should. */

        std::this_thread::sleep_for(std::chrono::milliseconds(SERVICE_SLEEP_TIME_MILLISECONDS));

    }

}

bool Switch::ServiceIter()
{

    StateCheck();

    return true;

}
