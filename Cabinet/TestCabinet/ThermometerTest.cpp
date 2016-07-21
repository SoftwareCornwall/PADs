#include <gtest/gtest.h>
#include "Thermometer.hpp"
#include "TemperatureCheck.hpp"
#include "OutputPinSpy.hpp"

TEST(ThermometerTests, test_if_0_is_a_fixed_point)
{
    int rawValue = 1;
    Thermometer thermometer1([&rawValue]()
    {
        return rawValue;
    });
    EXPECT_EQ(0, thermometer1.getTemperature());
}

TEST(ThermometerTests, test_if_500_is_entered_24_is_output)
{
    int rawValue = 500;
    Thermometer thermometer1([&rawValue]()
    {
        return rawValue;
    });
    EXPECT_EQ(24, thermometer1.getTemperature());
}



