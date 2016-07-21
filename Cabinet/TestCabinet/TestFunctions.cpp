#include "TestFunctions.hpp"
#include <algorithm>

bool IsSubstringPresentInOutputString(std::string subStr, std::string outputStr)
{
    auto foundStart = std::search(outputStr.begin(), outputStr.end(), subStr.begin(), subStr.end());

    if (foundStart != outputStr.end())
    {
        return true;
    }
    return false;

}
