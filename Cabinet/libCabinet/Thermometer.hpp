
#ifndef THERMOMETER_H
#define THERMOMETER_H
#include <functional>
#include <math.h>

class Thermometer
{
    public:
        Thermometer(std::function<int()> callback);
        void Service();//not sure yet
        int getTemp();
    protected:
    private:
        void TempConverter ();
        std::function<int()> tempReadCallback;
        int temperature = 11;//incase real temp is not yet processed, it does not trigger any checks

};

#endif // THERMOMETER_H
