
#ifndef TEMPERATURECHECK_H
#define TEMPERATURECHECK_H
#include "OutputPin.hpp"
#include <functional>

class TemperatureCheck
{
    public:
        TemperatureCheck (OutputPin *pin);
        void setTemperatureGetCallback(std::function<int()> callback);
        void service();
        int getTemperature();
        void setHeaterState(bool state);
    private:
        int temperature;
        bool heating = false;
        OutputPin *outputPin;
        std::function<int()> temperatureGetCallback;
};
#endif
