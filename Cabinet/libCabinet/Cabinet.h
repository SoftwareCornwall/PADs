#ifndef CABINET_H
#define CABINET_H

#include "Postman.h"
#include "Switch.hpp"
#include <chrono>

class Cabinet
{
    public:
        Cabinet(Postman *postie, std::string boxID);
        virtual ~Cabinet();
        bool DoorEventCallback(bool doorOpen);
        bool HangerEventCallback(bool hangerDown);
        void StatusService();
    protected:
    private:
       Postman *postie;
        Switch *doorSwitch;
        Switch *hangerSwitch;
        std::string boxID;
        std::chrono::high_resolution_clock::time_point lastMessageSentTime;
        bool doorIsOpen;
        bool hangerIsDown;
};

#endif // CABINET_H
