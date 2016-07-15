#include "Switch.hpp"
#include "TestPin.hpp"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(Switch, A_low_input_pin_indicates_the_switch_is_open)
{
    TestPin pin;
    pin.state = false;
    Switch doorSwitch{&pin};

    ASSERT_TRUE(doorSwitch.IsOpen());
}

TEST(Switch, A_high_input_pin_indicates_the_switch_is_not_open)
{
    TestPin pin;
    pin.state = true;

    Switch doorSwitch{&pin};

    ASSERT_FALSE(doorSwitch.IsOpen());
}
