#ifndef TESTPIN_H
#define TESTPIN_H

#include "InputPin.hpp"

class TestPin : public InputPin
{
public:
    bool state;
    bool State() override { return state; }
};

#endif
