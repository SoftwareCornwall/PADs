#include "HTTPPostClientSpy.h"

bool HTTPPostClientSpy::sendPostMsg(std::string URL, std::string data)
{
    lastPOSTURL = URL;
    lastPOSTData = data;
    return sendPostMsgResult;
}
