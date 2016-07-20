#include "CodeCheck.hpp"
#include <string>
#include <iostream>

CodeCheck::CodeCheck()
{
    inputConversion[0]='C';
    inputConversion[1]='9';
    inputConversion[2]='E';
    inputConversion[3]='0';
    inputConversion[4]='5';
    inputConversion[5]='7';
    inputConversion[6]='6';
    inputConversion[7]='8';
    inputConversion[8]='3';
    inputConversion[9]='1';
    inputConversion[10]='4';
    inputConversion[11]='2';

}

bool CodeCheck::InputCheck(std::string inputCode)
{
    std::string correctCode = "1234";
    if((inputCode == correctCode))
    {

        if(unlockCallback)
        {
            unlockCallback();
        }
        return true;
    }
    return false;

}

std::string CodeCheck::getCodeEntered()
{
    return codeEntered;
}

void CodeCheck::SetUnlockCallback (std::function<void()> callback)
{
    unlockCallback = callback;
}


void CodeCheck::keyPressed(int keyID)
{
    if (codeEntered.length() == maxLength || inputConversion[keyID] == 'C')
    {
        codeEntered = "";
    }
    else if (inputConversion[keyID] == 'E')
    {
        if (!InputCheck(codeEntered))
        {
            codeEntered = "";
        }
    }
    else
    {
        codeEntered += inputConversion[keyID];
    }
}


