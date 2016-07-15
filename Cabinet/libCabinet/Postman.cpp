#include "Postman.h"

Postman::Postman(std::string serverAddress, HTTPPostClient *client)
{
    postClient = client;
    this->serverAddress = serverAddress;
}

Postman::~Postman()
{
    //dtor
}

bool Postman::sendEventNotification(std::string boxID)
{
    return postClient->sendPostMsg(serverAddress, boxID);
}
