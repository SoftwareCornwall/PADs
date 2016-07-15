#include "Postman.h"

Postman::Postman(std::string serverAddress, HTTPPostClient *client)
{
    postClient = client;
    this->serverAddress = serverAddress;
}

bool Postman::sendEventNotification(std::string boxID)
{
    return postClient->sendPostMsg(serverAddress, boxID);
}
