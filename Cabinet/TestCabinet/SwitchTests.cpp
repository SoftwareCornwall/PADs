#include "Switch.hpp"
#include "TestPin.hpp"
#include <gtest/gtest.h>
#include <chrono>

using namespace ::testing;
using namespace ::std::chrono;

high_resolution_clock::time_point fakeTime;

high_resolution_clock::time_point currentTime()
{
    return fakeTime;
}

/*TEST(Switch, A_low_input_pin_indicates_the_switch_is_open)
{
    TestPin pin;
    pin.state = false;

    auto start = currentTime();

    milliseconds oneMillisecond{1};
    fakeTime += 3 * oneMillisecond;

    auto endTime = currentTime();

    milliseconds d = duration_cast<milliseconds>(endTime - start);

    std::cout << "duration is " << d.count() << std::endl;

    Switch doorSwitch{&pin};

    ASSERT_TRUE(doorSwitch.IsOpen());
}*/

TEST(Switch, Pin_state_low_indicates_switch_released)
{
    TestPin pin;
    pin.state = false;

    Switch doorSwitch{&pin};

    doorSwitch.StateCheck();

    ASSERT_FALSE(doorSwitch.IsPressed());
}


TEST(Switch, Pin_state_high_for_10ms_indicates_switch_pressed)
{
    fakeTime = high_resolution_clock::time_point();
    TestPin pin;
    pin.state = true;

    Switch doorSwitch{&pin};

    doorSwitch.StateCheck();
    ASSERT_FALSE(doorSwitch.IsPressed());

    fakeTime += milliseconds(9);
    doorSwitch.StateCheck();
    ASSERT_FALSE(doorSwitch.IsPressed());

    fakeTime += milliseconds(1);
    doorSwitch.StateCheck();
    ASSERT_TRUE(doorSwitch.IsPressed());

}

TEST(Switch, Pin_state_high_for_10ms_after_bounce_indicates_switch_pressed)
{
    fakeTime = high_resolution_clock::time_point();
    TestPin pin;
    pin.state = true;

    Switch doorSwitch{&pin};

    doorSwitch.StateCheck();
    ASSERT_FALSE(doorSwitch.IsPressed());

    fakeTime += milliseconds(1); //fakeTime = 1ms
    pin.state = false;
    doorSwitch.StateCheck();

    fakeTime += milliseconds(1); //fakeTime = 2ms
    pin.state = true;
    doorSwitch.StateCheck();

    fakeTime += milliseconds(5); //StateCheck at fakeTime = 7 ms
    doorSwitch.StateCheck();
    ASSERT_FALSE(doorSwitch.IsPressed());

    fakeTime += milliseconds(3); //fakeTime = 10ms
    doorSwitch.StateCheck();
    ASSERT_FALSE(doorSwitch.IsPressed());

    fakeTime += milliseconds(3); //fakeTime = 13ms
    doorSwitch.StateCheck();
    ASSERT_TRUE(doorSwitch.IsPressed());


}
