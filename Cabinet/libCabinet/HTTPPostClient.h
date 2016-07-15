#ifndef HTTPPOSTCLIENT_H
#define HTTPPOSTCLIENT_H

#include <string>

class HTTPPostClient
{
    public:
        virtual bool sendPostMsg(std::string URL, std::string data) = 0;
    protected:
    private:
};

#endif // HTTPPOSTCLIENT_H
