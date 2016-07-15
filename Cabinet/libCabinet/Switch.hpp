#ifndef SWITCH_H
#define SWITCH_H

#include "InputPin.hpp"
#include <chrono>

class Switch
{
private:
    InputPin *pin;
    bool PressedState;
    bool previouslyPressed;
    std::chrono::high_resolution_clock::time_point firstTime;
public:
    Switch(InputPin *doorPin);
    bool IsPressed();
    void StateCheck();
};

#endif
