#include <iostream>
#include <chrono>
#include <wiringPi.h>
#include <functional>

#include "WiringPiPin.hpp"
#include "LibCurlPostClient.h"
#include "Cabinet.h"
#include <thread>
#include <chrono>

#define SERVICE_SLEEP_TIME_MILLISECONDS 1

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

    LibCurlPostClient client = LibCurlPostClient();
    Postman pat(URL, &client);
    Cabinet cabinet(&pat, boxID);

    using namespace std::placeholders;

    auto doorEventCallback = std::bind(&Cabinet::DoorEventCallback, &cabinet, _1);

    WiringPiPin doorPin{0};
    Switch doorSwitch{&doorPin, doorEventCallback};

    while(true){

        doorSwitch.Service();

        /* Limit how fast ServiceIter is run, otherwise will deplete the
            battery quicker than it should. */

        std::this_thread::sleep_for(std::chrono::milliseconds(SERVICE_SLEEP_TIME_MILLISECONDS));

    }

    return 0;

}
