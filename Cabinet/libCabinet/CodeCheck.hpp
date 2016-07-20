#ifndef CODECHECK_H
#define CODECHECK_H
#include <string>
#include <map>
#include <iostream>
#include "OutputPin.hpp"
#include <functional>

class CodeCheck
{
    public:
        CodeCheck();
        bool InputCheck(std::string inputCode);
        void keyPressed(int keyID);
        std::string getCodeEntered();
        void SetUnlockCallback (std::function<void()> callback);
    protected:
    private:
        std::string codeEntered = "";
        const int maxLength = 20;
        std::map<int,char> inputConversion;
        std::function<void()> unlockCallback;


};

#endif
