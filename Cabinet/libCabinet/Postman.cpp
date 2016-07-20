#include "Postman.h"

Postman::Postman(std::string serverAddress, HTTPPostClient *client)
{
    postClient = client;
    this->serverAddress = serverAddress;
}

bool Postman::sendEventNotification(std::string boxID, std::string doorStatus, std::string hangerStatus)
{

    std::string boxPOSTData = "{\n"
    "  \"cabinet_id\" : \"" + boxID + "\", \n"
    "  \"door_status\" : \"" + doorStatus + "\", \n"
    "  \"hanger_status\" : \"" + hangerStatus + "\" \n"
    "}";

    return postClient->sendPostMsg(serverAddress, boxPOSTData);

}
