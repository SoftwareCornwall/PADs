#include <iostream>
#include <chrono>
#include <wiringPi.h>

#include "WiringPiPin.hpp"
#include "LibCurlPostClient.h"
#include "Cabinet.h"

using namespace std;
chrono::high_resolution_clock::time_point currentTime()
{
    return chrono::high_resolution_clock::now();
}

int main()
{
    wiringPiSetup();

    std::string boxID = "1111R";
    std::string URL = "http://servertobedecided.invalid/events";

    WiringPiPin doorPin{0};

    Switch doorSwitch{&doorPin};

    LibCurlPostClient client = LibCurlPostClient();
    Postman pat(URL, &client);
    Cabinet cabinet(&pat, &doorSwitch, boxID);

    cabinet.Service();

    return 0;
}
