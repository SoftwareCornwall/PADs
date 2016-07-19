#include "CodeCheck.hpp"
#include <string>
#include <iostream>

bool CodeCheck::InputCheck(std::string inputCode)
{
    std::string correctCode = "1234";
    if((inputCode == correctCode))
    {
        return true;
    }
    return false;

}

