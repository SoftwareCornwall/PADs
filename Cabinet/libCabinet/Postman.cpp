#include "Postman.h"

Postman::Postman(std::string serverAddress, HTTPPostClient *client)
{
    postClient = client;
    this->serverAddress = serverAddress;
}

bool Postman::sendEventNotification(std::string boxID, bool doorIsOpen, bool hangerIsDown)
{

    std::string doorStatus = "0"; // 0 is door closed
    if (doorIsOpen) doorStatus = "1"; // 1 is door open

    std::string hangerStatus = "1"; // 1 is defib removed
    if (hangerIsDown) hangerStatus = "0"; // 0 is defib present

    std::string boxPOSTData = "{\n"
    "  \"cabinet_id\" : \"" + boxID + "\", \n"
    "  \"door_open\" : \"" + doorStatus + "\", \n"
    "  \"defib_removed\" : \"" + hangerStatus + "\", \n"
    "  \"alarm_status\" : \"0\", \n"  // not implemented
    "  \"temp_status\" : \"15\" \n"  // not implemented
    "}";

    return postClient->sendPostMsg(serverAddress, boxPOSTData);

}
