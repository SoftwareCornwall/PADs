#include "WiringPiPin.hpp"
#include "Switch.hpp"
#include "MatrixKeypadReader.hpp"
#include "MatrixKeypad.hpp"
#include "CodeCheck.hpp"
#include "HBridgeLock.hpp"

#include "MCP3304.hpp"

#include <wiringPi.h>

#include <iostream>
#include <map>

using namespace std;

const map<int, char> keyMap =
{
    { 0,  'C' },
    { 1,  '9' },
    { 2,  'E' },
    { 3,  '0' },
    { 4,  '5' },
    { 5,  '7' },
    { 6,  '6' },
    { 7,  '8' },
    { 8,  '3' },
    { 9,  '1' },
    { 10, '4' },
    { 11, '2' }
};

int main()
{
    wiringPiSetup();

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

    keypad.SetKeyPressedCallback([](int key)
    {
        cout << "Key " << keyMap.at(key) << endl;
    });

    /**** Switches ****/
    WiringPiPin doorPin{2};
    WiringPiPin hangerPin{3};

    Switch doorSwitch(&doorPin, [&lock](bool state)
    {
        lock.Unlock();
        cout << "Door open" << endl;
    });

    Switch hangerSwitch(&hangerPin, [&lock](bool state)
    {
        lock.Lock();
        cout << "Hanger pressed" << endl;
    });

    WiringPiPin a2dChipSelect{};
    a2dChipSelect.ConfigureAsOutput();

    MCP3304 a2d{0, 500000, &a2dChipSelect};

    while(1)
    {
        doorSwitch.Service();
        hangerSwitch.Service();
        keypad.Service();
        lock.Service();
    }
    return 0;
}
