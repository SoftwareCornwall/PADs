#include "TemperatureCheck.hpp"

TemperatureCheck::TemperatureCheck(OutputPin *pin)
{
    outputPin = pin;
}
void TemperatureCheck::setTemperatureGetCallback(std::function<int()> callback)
{
    temperatureGetCallback = callback;
}

int TemperatureCheck::getTemperature()
{
    return temperature;
}

void TemperatureCheck::service()
{
    temperature = temperatureGetCallback();

     if (!heating && temperature <= 8)
    {
        heating = true;
        outputPin->State(heating);
    }
    else if (heating && temperature>=15)
    {
        heating = false;
        outputPin->State(heating);
    }
}

void TemperatureCheck::setHeaterState(bool state)
{
    heating = state;
}
