#ifndef CABINET_H
#define CABINET_H

#include "Postman.h"
#include "Switch.hpp"

class Cabinet
{
    public:
        Cabinet(Postman *postie, Switch *doorSwitch, std::string boxID);
        virtual ~Cabinet();
        void Service();
        bool ServiceIter();
    protected:
    private:
        Postman *postie;
        Switch *doorSwitch;
        std::string boxID;
};

#endif // CABINET_H
