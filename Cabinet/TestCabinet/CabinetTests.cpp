#include "Cabinet.h"
#include <chrono>
#include <gtest/gtest.h>
#include <functional>

#include "HTTPPostClientSpy.h"
#include "Postman.h"

#include "TestPin.hpp"
#include "TestTime.hpp"
#include "Switch.hpp"


#include "TestFunctions.hpp"


using namespace ::testing;
using namespace ::std::chrono;

class CabinetTests : public Test
{
public:

    std::string boxID = "AA123";
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

    cabinet.DoorEventCallback(true);
    ASSERT_TRUE(IsSubstringPresentInOutputString("  \"door_open\" : \"1\", \n", client.lastPOSTData));
    ASSERT_EQ(URL, client.lastPOSTURL);

}

TEST_F(CabinetTests, Cabinet_sends_status_at_fifteen_minute_intervals)
{

    fakeTime = high_resolution_clock::time_point();

    client.lastPOSTData = "";
    cabinet.StatusService();
    ASSERT_EQ("", client.lastPOSTData);

    fakeTime += minutes(5); // 5 mins
    cabinet.StatusService();
    ASSERT_EQ("", client.lastPOSTData);

    fakeTime += minutes(5); // 10 mins
    cabinet.StatusService();
    ASSERT_EQ("", client.lastPOSTData);

    fakeTime += minutes(6); // 16 mins
    cabinet.StatusService();
    ASSERT_NE("", client.lastPOSTData);
    ASSERT_TRUE(IsSubstringPresentInOutputString("cabinet_id", client.lastPOSTData));

    client.lastPOSTData = "";
    fakeTime += minutes(4); // 20 mins
    cabinet.StatusService();
    ASSERT_EQ("", client.lastPOSTData);
    ASSERT_FALSE(IsSubstringPresentInOutputString("cabinet_id", client.lastPOSTData));

}

TEST_F(CabinetTests, Cabinet_status_message_reflects_changes_in_switch_status)
{

    fakeTime = high_resolution_clock::time_point();

    client.lastPOSTData = "";
    cabinet.DoorEventCallback(true);
    fakeTime += minutes(16); // 16 mins
    cabinet.StatusService();
    ASSERT_TRUE(IsSubstringPresentInOutputString("  \"door_open\" : \"1\", \n", client.lastPOSTData));

    client.lastPOSTData = "";
    cabinet.DoorEventCallback(false);
    fakeTime += minutes(16); // 16 mins
    cabinet.StatusService();
    ASSERT_TRUE(IsSubstringPresentInOutputString("  \"door_open\" : \"0\", \n", client.lastPOSTData));

    client.lastPOSTData = "";
    cabinet.HangerEventCallback(true);
    fakeTime += minutes(16); // 16 mins
    cabinet.StatusService();
    ASSERT_TRUE(IsSubstringPresentInOutputString("  \"defib_removed\" : \"0\", \n", client.lastPOSTData));

    client.lastPOSTData = "";
    cabinet.HangerEventCallback(false);
    fakeTime += minutes(16); // 16 mins
    cabinet.StatusService();
    ASSERT_TRUE(IsSubstringPresentInOutputString("  \"defib_removed\" : \"1\", \n", client.lastPOSTData));

}

