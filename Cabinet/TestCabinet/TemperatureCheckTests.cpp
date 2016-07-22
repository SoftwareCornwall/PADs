#include <gtest/gtest.h>
#include "TemperatureCheck.hpp"
#include "OutputPinSpy.hpp"



TEST(TemperatureCheckTests, When_temperature_measured_betweeen_8_and_15_and_not_heating_do_not_heat)
{
    OutputPinSpy outputPin;
    TemperatureCheck temperatureCheck(&outputPin);

    int temperature = 14;
    temperatureCheck.setHeaterState(false);

    temperatureCheck.setTemperatureGetCallback([&temperature]()
    {
        return temperature;
    });
    temperatureCheck.service();
    EXPECT_EQ(false,outputPin.getState());
}



TEST(TemperatureCheckTests, When_temperature_measured_below_8_and_heater_not_on_turn_on)
{
    OutputPinSpy outputPin;
    TemperatureCheck temperatureCheck(&outputPin);
    temperatureCheck.setHeaterState(false);

    int temperature = 7;

    temperatureCheck.setTemperatureGetCallback([&temperature]()
    {
        return temperature;
    });
    temperatureCheck.service();
    EXPECT_EQ(true,outputPin.getState());
}

TEST(TemperatureCheckTests, When_temperature_measured_below_8_and_heater_is_on_dont_change_outputPin)
{
    OutputPinSpy outputPin;
    TemperatureCheck temperatureCheck(&outputPin);
    outputPin.State(false);
    temperatureCheck.setHeaterState(true);

    int temperature = 7;
    temperatureCheck.setTemperatureGetCallback([&temperature]()
    {
        return temperature;
    });
    temperatureCheck.service();
    EXPECT_EQ(false,outputPin.getState());
}


TEST(TemperatureCheckTests, When_heater_is_on_and_temperature_is_15_or_over_turn_heater_off)
{

    OutputPinSpy outputPin;
    TemperatureCheck temperatureCheck(&outputPin);
    temperatureCheck.setHeaterState(true);
    outputPin.State(true);


    int temperature = 16;


    temperatureCheck.setTemperatureGetCallback([&temperature]()
    {
        return temperature;
    });
    temperatureCheck.service();
    EXPECT_EQ(false,outputPin.getState());
}

TEST(TemperatureCheckTests, When_temperature_measured_betweeen_8_and_15_and_heating_do_not_change_OutputPin)
{
    OutputPinSpy outputPin;
    TemperatureCheck temperatureCheck(&outputPin);

    int temperature = 12;
    temperatureCheck.setHeaterState(true);
    outputPin.State(true);

    temperatureCheck.setTemperatureGetCallback([&temperature]()
    {
        return temperature;
    });
    temperatureCheck.service();
    EXPECT_EQ(true,outputPin.getState());
}

