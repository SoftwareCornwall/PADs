#include "WiringPiPin.hpp"
#include "Switch.hpp"
#include "MatrixKeypadReader.hpp"
#include "MatrixKeypad.hpp"
#include "CodeCheck.hpp"

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

    WiringPiPin doorPin{2};
    WiringPiPin hangerPin{3};

    WiringPiPin column1{27};
    WiringPiPin column2{28};
    WiringPiPin column3{29};

    WiringPiPin row1{22};
    WiringPiPin row2{23};
    WiringPiPin row3{24};
    WiringPiPin row4{25};

    Switch doorSwitch(&doorPin, [](bool state)
    {
        cout << "Door open" << endl;
    });

    Switch hangerSwitch(&hangerPin, [](bool state)
    {
        cout << "Hanger pressed" << endl;
    });

    column1.ConfigureAsOutput();
    column2.ConfigureAsOutput();
    column3.ConfigureAsOutput();

    MatrixKeypadReader reader{&column1, &column2, &column3, &row1, &row2, &row3, &row4};
    MatrixKeypad keypad{&reader};

    keypad.SetKeyPressedCallback([](int key)
    {
        cout << "Key " << keyMap.at(key) << endl;
    });

    while(1)
    {
        doorSwitch.Service();
        hangerSwitch.Service();
        keypad.Service();
    }
    return 0;
}
