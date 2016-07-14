#include "Switch.hpp"

Switch::Switch(InputPin *doorPin)
{
    pin = doorPin;
}

bool Switch::IsOpen()
{
    return !pin->State();
}
