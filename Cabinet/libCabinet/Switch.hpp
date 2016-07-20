#ifndef SWITCH_H
#define SWITCH_H

#include <functional>
#include <chrono>

#include "InputPin.hpp"

using doorCallback = std::function<void(bool)>;

class Switch
{
public:
    Switch(InputPin *doorPin, doorCallback doorEventCallback);
    bool IsPressed();
    void StateCheck();
    void Service();
private:
    InputPin *pin;
    bool pressedState;
    bool previouslyPressed;
    std::chrono::high_resolution_clock::time_point firstTime;
    doorCallback doorCallbackFunction;
};

#endif
