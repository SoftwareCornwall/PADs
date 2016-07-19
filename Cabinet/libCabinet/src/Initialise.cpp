#include "Initialise.h"

using namespace std;


Initialise::Initialise()
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

    using namespace std::placeholders;
    keypad.SetKeyPressedCallback(std::bind(&CodeCheck::keyPressed, &codeChecker, _1));
    codeChecker.SetUnlockCallback(std::bind(&HBridgeLock::Unlock, &lock));


    while(1)
    {
        keypad.Service();
        lock.Service();
    }//ctor
}
