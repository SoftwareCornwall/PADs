#include <chrono>
#include <gtest/gtest.h>
#include <functional>

#include "HTTPPostClientSpy.h"
#include "Postman.h"

#include "TestPin.hpp"
#include "TestTime.hpp"
#include "Switch.hpp"

#include "Cabinet.h"

using namespace ::testing;
using namespace ::std::chrono;

class CabinetTests : public Test
{
public:

    std::string boxID = "114";
    std::string URL = "http://gibberish.invalid/";
    HTTPPostClientSpy client;
    Postman postie;
    Cabinet cabinet;

    CabinetTests() : client(),
                     postie(URL, &client),
                     cabinet(&postie, boxID)
    {
    }

};

TEST_F(CabinetTests, Cabinet_sends_event_after_door_open_event)
{

    //setDoorSwitchState(false);

    client.sendPostMsgResult = true;

    std::string boxPOSTData = "{\n"
    "  \"cabinet_id\" : \"" + boxID + "\", \n"
    "  \"door_status\" : \"Open\", \n"
    "  \"defib_status\" : \"Available\" \n"
    "}";

    cabinet.DoorEventCallback(true);
    ASSERT_EQ(boxPOSTData, client.lastPOSTData);
    ASSERT_EQ(URL, client.lastPOSTURL);

}

