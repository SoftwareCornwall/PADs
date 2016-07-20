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

class HangerTests : public Test
{
public:

    std::string boxID = "114";
    std::string URL = "http://gibberish.invalid/";
    HTTPPostClientSpy client;
    Postman postie;
    Cabinet cabinet;

    HangerTests() : client(),
                     postie(URL, &client),
                     cabinet(&postie, boxID)
    {
    }

};

TEST_F(HangerTests, Cabinet_sends_event_after_hanger_weight_release_event)
{

    //setDoorSwitchState(false);

    client.sendPostMsgResult = true;

    cabinet.HangerEventCallback(true);
    ASSERT_TRUE(cabinet.IsSubstringPresentInOutputString("  \"hanger_status\" : \"Down\" \n", client.lastPOSTData));
    ASSERT_EQ(URL, client.lastPOSTURL);

}
