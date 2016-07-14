#include "WiringPiPin.hpp"
#include "WiringPiPin.hpp"
#include <wiringPi.h>

WiringPiPin::WiringPiPin(int pinNumber) :
    pinNumber(pinNumber)
{
    pinMode(pinNumber, INPUT);
}

bool WiringPiPin::State()
{
    return digitalRead(pinNumber);
}
