#include "Switch.hpp"
#include "CurrentTime.hpp"
#include <thread>
#include <chrono>

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

    StateCheck();

}
