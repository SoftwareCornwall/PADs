#ifndef WIRINGPIPIN_H
#define WIRINGPIPIN_H

#include "InputPin.hpp"
#include "OutputPin.hpp"

class WiringPiPin : public InputPin, public OutputPin
{
private:
    const int pinNumber;
public:
    WiringPiPin(int pinNumber);
    bool State() override;
    void State(bool state) override;
    void ConfigureAsOutput();
};

#endif // WIRINGPIPIN_H
