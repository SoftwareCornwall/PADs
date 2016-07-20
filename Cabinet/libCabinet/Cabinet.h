#ifndef CABINET_H
#define CABINET_H

#include "Postman.h"
#include "Switch.hpp"

class Cabinet
{
    public:
        Cabinet(Postman *postie, std::string boxID);
        virtual ~Cabinet();
        bool DoorEventCallback(bool doorOpen);
        bool HangerEventCallback(bool hangerDown);
        bool IsSubstringPresentInOutputString(std::string subStr, std::string outputStr);
    protected:
    private:
        Postman *postie;
        Switch *doorSwitch;
        std::string boxID;
};

#endif // CABINET_H
