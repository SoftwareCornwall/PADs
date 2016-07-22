#include "Switch.hpp"
#include "TestPin.hpp"
#include "TestTime.hpp"
#include "Cabinet.h"
#include "HTTPPostClientSpy.h"
#include <gtest/gtest.h>
#include <chrono>
#include <functional>
#include <string>

using namespace ::testing;
using namespace ::std::chrono;

class SwitchTests : public Test
{
public:

    std::string boxID = "114";
    std::string URL = "http://gibberish.invalid/";
    HTTPPostClientSpy client;
    Postman postie;
    Cabinet cabinet;
    doorCallback doorSwitchCallback;
    TestPin pin;
    Switch doorSwitch;
    bool callbackState;

    SwitchTests() : postie(URL, &client),
                    cabinet(&postie, boxID),
                    doorSwitchCallback(std::bind(&Cabinet::DoorEventCallback, cabinet, std::placeholders::_1)),
                    doorSwitch{&pin, [this](bool state) { callbackState = state; }}
    {
    }

    void TimeElapseTest(int iTime)
    {
        fakeTime += milliseconds(iTime);
        doorSwitch.StateCheck();
        ASSERT_FALSE(doorSwitch.IsPressed());
    }

};

TEST_F(SwitchTests, Pin_state_low_indicates_switch_released)
{
    pin.state = false;

    doorSwitch.StateCheck();

    ASSERT_FALSE(doorSwitch.IsPressed());
}


TEST_F(SwitchTests, Pin_state_high_for_10ms_indicates_switch_pressed)
{
    fakeTime = high_resolution_clock::time_point();
    pin.state = true;
    callbackState = false;

    TimeElapseTest(0);

    TimeElapseTest(9);

    fakeTime += milliseconds(1);
    doorSwitch.StateCheck();
    ASSERT_TRUE(doorSwitch.IsPressed());

    ASSERT_TRUE(callbackState);

}

TEST_F(SwitchTests, Pin_state_high_for_10ms_after_bounce_indicates_switch_pressed)
{
    fakeTime = high_resolution_clock::time_point();
    pin.state = true;

    doorSwitch.StateCheck();
    ASSERT_FALSE(doorSwitch.IsPressed());

    pin.state = false;
    TimeElapseTest(1); //fakeTime = 1ms

    pin.state = true;
    TimeElapseTest(1); //fakeTime = 2ms

    TimeElapseTest(5); //StateCheck at fakeTime = 7 ms

    TimeElapseTest(3); //fakeTime = 10ms

    fakeTime += milliseconds(3); //fakeTime = 13ms
    doorSwitch.StateCheck();
    ASSERT_TRUE(doorSwitch.IsPressed());
}

TEST_F(SwitchTests, Pin_state_low_after_10ms_high_indicates_switch_released)
{
    fakeTime = high_resolution_clock::time_point();
    pin.state = true;
    callbackState = false;

    TimeElapseTest(0);

    TimeElapseTest(9);

    fakeTime += milliseconds(1);
    doorSwitch.StateCheck();

    ASSERT_TRUE(doorSwitch.IsPressed());

    pin.state = false;
    doorSwitch.StateCheck();

    ASSERT_FALSE(callbackState);

    // Check callback only happens once
    callbackState = true;
    doorSwitch.StateCheck();

    ASSERT_TRUE(callbackState);
}
