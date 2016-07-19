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
    pressedState = false;
}

bool Switch::IsPressed()
{
    return pressedState;
}

void Switch::StateCheck()
{

    if(pin->State() == false)
    {
        pressedState = false;
        previouslyPressed = false;
    }
    else
    {

        if (previouslyPressed == false)
        {
            firstTime = CurrentTime();

        }
        else
        {
           if (((CurrentTime() - firstTime) >= milliseconds(10)) && !pressedState)
           {
                doorCallbackFunction(true);
                pressedState = true;
           }
        }
        previouslyPressed = true;

    }

}

void Switch::Service()
{

    StateCheck();

}
