#include "Switch.hpp"
#include "CurrentTime.hpp"

using namespace ::std::chrono;

Switch::Switch(InputPin *doorPin)
{
    pin = doorPin;
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
           }
        }
        previouslyPressed = true;

    }
}
