#include "CodeCheck.hpp"
#include <string>
#include <iostream>

CodeCheck::CodeCheck()
{
    inputConversion[0]='0';
    inputConversion[1]='1';
    inputConversion[2]='2';
    inputConversion[3]='3';
    inputConversion[4]='4';
    inputConversion[5]='5';
    inputConversion[6]='6';
    inputConversion[7]='7';
    inputConversion[8]='8';
    inputConversion[9]='9';
    inputConversion[10]='e';
    inputConversion[11]='c';

}

bool CodeCheck::inputCheck(std::string inputCode)
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
    if (codeEntered.length() == maxLength || inputConversion[keyID] == 'c')
    {
        codeEntered = "";
    }
    else if (inputConversion[keyID] == 'e')
    {
        if (!inputCheck(codeEntered))
        {
            codeEntered = "";
        }
    }
    else
    {
        codeEntered += inputConversion[keyID];
    }
}


