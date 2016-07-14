#include <iostream>
#include <wiringPi.h>
#include "Switch.hpp"
#include "WiringPiPin.hpp"

using namespace std;

int main()
{
    wiringPiSetup();

    WiringPiPin doorPin{0};

    Switch doorSwitch{&doorPin};

    return 0;
}
