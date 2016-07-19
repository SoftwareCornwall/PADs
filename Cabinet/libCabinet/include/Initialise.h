#ifndef INITIALISE_H
#define INITIALISE_H

#include "CodeCheck.hpp"
#include "WiringPiPin.hpp"
#include "MatrixKeypad.hpp"
#include "HBridgeLock.hpp"
#include <wiringPi.h>
#include <iostream>

class Initialise
{
    public:
        Initialise();
    protected:
    private:
        CodeCheck codeChecker;
};

#endif // INITIALISE_H
