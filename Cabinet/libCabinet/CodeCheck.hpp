#ifndef CODECHECK_H
#define CODECHECK_H
#include <string>
#include <map>
#include <iostream>
#include "OutputPin.hpp"

class CodeCheck
{
    public:
        CodeCheck(OutputPin *OutputPin);
        bool inputCheck(std::string inputCode);
        void keyPressed(int keyID);
        bool getPinState();
        std::string getCodeEntered();
    protected:
    private:
        std::string codeEntered = "";
        const int maxLength = 20;
        std::map<int,char> inputConversion;
        OutputPin *doorOutputPin;


};

#endif
