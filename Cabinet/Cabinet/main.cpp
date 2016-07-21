#include <iostream>
#include <chrono>
#include <wiringPi.h>
#include <functional>
#include "CodeCheck.hpp"
#include "WiringPiPin.hpp"
#include "MatrixKeypad.hpp"
#include "HBridgeLock.hpp"

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
    std::string URL = "http://192.168.0.110/events/";

    LibCurlPostClient client = LibCurlPostClient();
    Postman pat(URL, &client);
    Cabinet cabinet(&pat, boxID);

    using namespace std::placeholders;

    auto doorEventCallback = std::bind(&Cabinet::DoorEventCallback, &cabinet, _1);

    WiringPiPin doorPin{2};
    Switch doorSwitch{&doorPin, doorEventCallback};

    /**** hanger switch ****/

    auto hangerEventCallback = std::bind(&Cabinet::HangerEventCallback, &cabinet, _1);

    WiringPiPin hangerPin{3};
    Switch hangerSwitch{&hangerPin, hangerEventCallback};


    /**** H-Bridge Lock ****/
    WiringPiPin lockOpen{0};
    WiringPiPin lockClose{7};

    // If the program has been run before then make
    // sure both of the pins are low before configuring
    // either of them as outputs
    lockOpen.State(false);
    lockClose.State(false);

    lockOpen.ConfigureAsOutput();
    lockOpen.State(false);
    // IMPORTANT - make sure the Open pin is low before
    // changing the Close pin to an output to avoid
    // shorting the power rails
    lockClose.ConfigureAsOutput();
    lockClose.State(false);

    HBridgeLock lock{&lockOpen, &lockClose};

    /**** Matrix Keypad ****/
    WiringPiPin column1{27};
    WiringPiPin column2{28};
    WiringPiPin column3{29};

    WiringPiPin row1{22};
    WiringPiPin row2{23};
    WiringPiPin row3{24};
    WiringPiPin row4{25};

    column1.ConfigureAsOutput();
    column2.ConfigureAsOutput();
    column3.ConfigureAsOutput();

    MatrixKeypadReader reader{&column1, &column2, &column3, &row1, &row2, &row3, &row4};
    MatrixKeypad keypad{&reader};

    CodeCheck codeChecker;

    using namespace std::placeholders;
    keypad.SetKeyPressedCallback(std::bind(&CodeCheck::keyPressed, &codeChecker, _1));
    codeChecker.SetUnlockCallback(std::bind(&HBridgeLock::Unlock, &lock));


    while(true)
    {
        keypad.Service();
        lock.Service();

        doorSwitch.Service();
        hangerSwitch.Service();

        cabinet.StatusService();

        /* Limit how fast ServiceIter is run, otherwise will deplete the
            battery quicker than it should. */

        std::this_thread::sleep_for(std::chrono::milliseconds(SERVICE_SLEEP_TIME_MILLISECONDS));

    }

    return 0;

}
