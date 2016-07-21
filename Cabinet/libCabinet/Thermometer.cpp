
#include "Thermometer.hpp"

Thermometer::Thermometer(std::function<int()> callback)
{
    temperatureReadCallback = callback;
}

void Thermometer::TemperatureConverter ()
{
    int rawValue = temperatureReadCallback();
    temperature = round((((float)rawValue * 50) / 65535));
}

int Thermometer::getTemperature()
{
    TemperatureConverter();
    return temperature;
}
