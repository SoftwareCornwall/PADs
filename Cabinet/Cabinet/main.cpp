#include <iostream>
#include <wiringPi.h>
#include "Switch.hpp"
#include "WiringPiPin.hpp"
#include <chrono>

using namespace std;
chrono::high_resolution_clock::time_point currentTime()
{
    return chrono::high_resolution_clock::now();
}

int main()
{
    wiringPiSetup();

    WiringPiPin doorPin{0};

    Switch doorSwitch{&doorPin};

    return 0;
}
