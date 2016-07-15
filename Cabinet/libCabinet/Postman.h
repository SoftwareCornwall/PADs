
#ifndef POSTMAN_H
#define POSTMAN_H

#include <string>
#include "HTTPPostClient.h"

class Postman
{
    public:
        Postman(std::string serverAddress, HTTPPostClient *client);
        virtual ~Postman();
        bool sendEventNotification(std::string boxID);
    protected:
    private:
        std::string serverAddress;
        HTTPPostClient *postClient;
};

#endif // POSTMAN_H