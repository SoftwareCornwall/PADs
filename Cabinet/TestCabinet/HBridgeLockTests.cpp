#include "HBridgeLock.hpp"
#include <gtest/gtest.h>

#include "TestTime.hpp"
#include "OutputPinSpy.hpp"

using namespace ::testing;
using namespace ::std::chrono;



class HBridgeLockTests : public Test
{
public:
    OutputPinSpy openPin;
    OutputPinSpy closePin;

    HBridgeLockTests()
    {
        fakeTime = high_resolution_clock::time_point();
    }

    void Reset_stateSet()
    {
        openPin.stateSet = false;
        closePin.stateSet = false;
    }
};

TEST_F(HBridgeLockTests, The_open_and_close_pins_are_both_set_to_output_low_when_the_object_is_created)
{
    HBridgeLock lock{&openPin, &closePin};

    ASSERT_TRUE(openPin.stateSet);
    ASSERT_FALSE(openPin.state);

    ASSERT_TRUE(closePin.stateSet);
    ASSERT_FALSE(closePin.state);
}

TEST_F(HBridgeLockTests, Locking_will_cause_the_close_pin_to_go_high_for_500ms)
{
    HBridgeLock lock{&openPin, &closePin};
    Reset_stateSet();

    lock.Lock();

    lock.Service();
    ASSERT_TRUE(closePin.state);

    fakeTime += milliseconds(499);
    lock.Service();
    ASSERT_TRUE(closePin.state);

    fakeTime += milliseconds(1);
    lock.Service();
    ASSERT_FALSE(closePin.state);

    ASSERT_FALSE(openPin.stateSet);
}

TEST_F(HBridgeLockTests, Unlocking_will_cause_the_open_pin_to_go_high_for_500ms)
{
    HBridgeLock lock{&openPin, &closePin};
    Reset_stateSet();

    lock.Unlock();

    lock.Service();
    ASSERT_TRUE(openPin.state);

    fakeTime += milliseconds(499);
    lock.Service();
    ASSERT_TRUE(openPin.state);

    fakeTime += milliseconds(1);
    lock.Service();
    ASSERT_FALSE(openPin.state);

    ASSERT_FALSE(closePin.stateSet);
}

TEST_F(HBridgeLockTests, Requesting_a_Lock_then_an_Unlock_will_only_start_the_Lock)
{
    HBridgeLock lock{&openPin, &closePin};
    Reset_stateSet();

    lock.Lock();
    lock.Unlock();

    lock.Service();
    ASSERT_TRUE(closePin.state);

    fakeTime += milliseconds(500);
    lock.Service();
    ASSERT_FALSE(closePin.state);

    ASSERT_FALSE(openPin.stateSet);
}

TEST_F(HBridgeLockTests, Requesting_a_Unlock_in_the_middle_of_a_Lock_does_not_start_the_Unlock)
{
    HBridgeLock lock{&openPin, &closePin};
    Reset_stateSet();

    lock.Lock();

    lock.Service();
    ASSERT_TRUE(closePin.state);

    fakeTime += milliseconds(1);
    lock.Service();
    ASSERT_TRUE(closePin.state);

    lock.Unlock();

    fakeTime += milliseconds(499);
    lock.Service();
    ASSERT_FALSE(closePin.state);

    ASSERT_FALSE(openPin.stateSet);
}

TEST_F(HBridgeLockTests, Requesting_an_Unlock_then_an_Lock_will_only_start_the_Unlock)
{
    HBridgeLock lock{&openPin, &closePin};
    Reset_stateSet();

    lock.Unlock();
    lock.Lock();

    lock.Service();
    ASSERT_TRUE(openPin.state);

    fakeTime += milliseconds(500);
    lock.Service();
    ASSERT_FALSE(openPin.state);

    ASSERT_FALSE(closePin.stateSet);
}

TEST_F(HBridgeLockTests, Requesting_a_Lock_in_the_middle_of_an_Unlock_does_not_start_the_Lock)
{
    HBridgeLock lock{&openPin, &closePin};
    Reset_stateSet();

    lock.Unlock();

    lock.Service();
    ASSERT_TRUE(openPin.state);

    fakeTime += milliseconds(1);
    lock.Service();
    ASSERT_TRUE(openPin.state);

    lock.Lock();

    fakeTime += milliseconds(499);
    lock.Service();
    ASSERT_FALSE(openPin.state);

    ASSERT_FALSE(closePin.stateSet);
}
