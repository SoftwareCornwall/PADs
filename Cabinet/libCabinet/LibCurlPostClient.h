#ifndef LIBCURLPOSTCLIENT_H
#define LIBCURLPOSTCLIENT_H
#include <curl/curl.h>
#include "HTTPPostClient.h"

class LibCurlPostClient : public HTTPPostClient
{
    public:
        bool SendPostMsg(std::string URL, std::string data);
    protected:
    private:
        CURL *curl;
        CURLcode res;
};

#endif // LIBCURLPOSTCLIENT_H
