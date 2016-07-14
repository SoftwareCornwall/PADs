#ifndef SWITCH_H
#define SWITCH_H

#include "InputPin.hpp"

class Switch
{
private:
    InputPin *pin;
public:
    Switch(InputPin *doorPin);
    bool IsOpen();
};

#endif
