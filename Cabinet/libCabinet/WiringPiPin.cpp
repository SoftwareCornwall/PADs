#include "WiringPiPin.hpp"
#include <wiringPi.h>

WiringPiPin::WiringPiPin(int pinNumber) :
    pinNumber(pinNumber)
{
    pinMode(pinNumber, INPUT);
}

void WiringPiPin::ConfigureAsOutput()
{
    pinMode(pinNumber, OUTPUT);
    State(false);
}

bool WiringPiPin::State()
{
    return digitalRead(pinNumber);
}

void WiringPiPin::State(bool state)
{
    digitalWrite(pinNumber, state ? HIGH : LOW);
}
