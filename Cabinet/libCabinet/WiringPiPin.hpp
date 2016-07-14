#ifndef WIRINGPIPIN_H
#define WIRINGPIPIN_H

#include "InputPin.hpp"

class WiringPiPin : public InputPin
{
private:
    const int pinNumber;
public:
    WiringPiPin(int pinNumber);
    bool State() override;
};

#endif // WIRINGPIPIN_H
