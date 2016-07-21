#include "Postman.h"

Postman::Postman(std::string serverAddress, HTTPPostClient *client)
{
    postClient = client;
    this->serverAddress = serverAddress;
}

bool Postman::sendEventNotification(std::string boxID, bool doorIsOpen, bool hangerIsDown)
{

    std::string doorStatus = "Closed";
    if (doorIsOpen) doorStatus = "Open";

    std::string hangerStatus = "Up";
    if (hangerIsDown) hangerStatus = "Down";

    std::string boxPOSTData = "{\n"
    "  \"cabinet_id\" : \"" + boxID + "\", \n"
    "  \"door_status\" : \"" + doorStatus + "\", \n"
    "  \"hanger_status\" : \"" + hangerStatus + "\" \n"
    "}";

    return postClient->sendPostMsg(serverAddress, boxPOSTData);

}
