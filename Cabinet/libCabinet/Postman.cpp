#include "Postman.h"

Postman::Postman(std::string serverAddress, HTTPPostClient *client)
{
    postClient = client;
    this->serverAddress = serverAddress;
}

bool Postman::SendEventNotification(std::string boxID, std::string doorStatus, std::string defibStatus)
{

    std::string boxPOSTData = "{\n"
    "  \"cabinet_id\" : \"" + boxID + "\", \n"
    "  \"door_status\" : \"" + doorStatus + "\", \n"
    "  \"defib_status\" : \"" + defibStatus + "\" \n"
    "}";

    return postClient->SendPostMsg(serverAddress, boxPOSTData);

}
