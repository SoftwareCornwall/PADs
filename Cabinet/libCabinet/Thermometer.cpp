
#include "Thermometer.hpp"

Thermometer::Thermometer(std::function<int()> callback)
{
    tempReadCallback = callback;
}

void Thermometer::TempConverter ()
{
    int rawValue = tempReadCallback();
    temperature = round((((float)rawValue * 50) / 1023));
}

int Thermometer::getTemp()
{
    TempConverter();
    return temperature;
}
