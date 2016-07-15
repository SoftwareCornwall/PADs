#include "HTTPPostClientSpy.h"

HTTPPostClientSpy::HTTPPostClientSpy()
{
    //ctor
}

HTTPPostClientSpy::~HTTPPostClientSpy()
{
    //dtor
}

bool HTTPPostClientSpy::sendPostMsg(std::string URL, std::string data)
{
    lastPOSTURL = URL;
    lastPOSTData = data;
    return sendPostMsgResult;
}
