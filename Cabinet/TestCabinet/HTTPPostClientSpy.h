#ifndef HTTPPOSTCLIENTSPY_H
#define HTTPPOSTCLIENTSPY_H

#include "HTTPPostClient.h"


class HTTPPostClientSpy : public HTTPPostClient
{
    public:
        bool SendPostMsg(std::string URL, std::string data);
        bool sendPostMsgResult = false;
        std::string lastPOSTURL;
        std::string lastPOSTData;
    protected:
    private:
};

#endif // HTTPPOSTCLIENTSPY_H
