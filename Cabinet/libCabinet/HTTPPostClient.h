#ifndef HTTPPOSTCLIENT_H
#define HTTPPOSTCLIENT_H

#include <string>

class HTTPPostClient
{
    public:
        virtual bool SendPostMsg(std::string URL, std::string data) = 0;
        virtual ~HTTPPostClient(){};
    protected:
    private:
};

#endif // HTTPPOSTCLIENT_H
