#include <chrono>
#include <gtest/gtest.h>

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
    TestPin pin;
    Switch doorSwitch;
    HTTPPostClientSpy client;
    Postman postie;
    Cabinet cabinet;

    CabinetTests() : doorSwitch{&pin},
                     client(),
                     postie(URL, &client),
                     cabinet(&postie, &doorSwitch, boxID)
    {
    }

    void TimeElapseTest(int iTime)
    {
        fakeTime += milliseconds(iTime);
        doorSwitch.StateCheck();
        ASSERT_FALSE(doorSwitch.IsPressed());
    }

    void setDoorSwitchState(bool state)
    {
        fakeTime = high_resolution_clock::time_point();
        pin.state = state;

        TimeElapseTest(0);

        TimeElapseTest(9);

        fakeTime += milliseconds(1);
        doorSwitch.StateCheck();
    }

};

TEST_F(CabinetTests, Cabinet_sends_event_after_door_open_event)
{

    setDoorSwitchState(false);

    client.sendPostMsgResult = true;

    std::string boxPOSTData = "{\n"
    "  \"cabinet_id\" : \"" + boxID + "\", \n"
    "  \"door_status\" : \"Open\", \n"
    "  \"defib_status\" : \"Available\" \n"
    "}";

    ASSERT_TRUE(cabinet.ServiceIter());
    ASSERT_EQ(boxPOSTData, client.lastPOSTData);
    ASSERT_EQ(URL, client.lastPOSTURL);

}

