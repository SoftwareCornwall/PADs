#ifndef OUTPUTPINSPY_HPP
#define OUTPUTPINSPY_HPP
#include "OutputPin.hpp"

class OutputPinSpy : public OutputPin
{
public:
    bool state=false;
    bool stateSet=false;

    void State(bool state) override
    {
        this->state = state;
        stateSet = true;
    }
    bool getState()
    {
        return this->state;
    }
};


#endif

