#include "HTTPPostClientSpy.h"

bool HTTPPostClientSpy::SendPostMsg(std::string URL, std::string data)
{
    lastPOSTURL = URL;
    lastPOSTData = data;
    return sendPostMsgResult;
}
