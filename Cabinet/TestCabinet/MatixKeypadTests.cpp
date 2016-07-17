#include "MatrixKeypad.hpp"
#include "MatrixKeypadReader.hpp"
#include "MatrixKeypadPinsFake.hpp"
#include <gtest/gtest.h>
#include <chrono>

using namespace ::std::chrono;
using namespace ::testing;

extern high_resolution_clock::time_point fakeTime;

class MatrixKeypadTests : public Test
{
public:
    MatrixKeypadPinsFake pins;
    MatrixKeypadReader keypadReader;
    MatrixKeypad keypad;

    bool keyState;
    int column;
    int row;

    MatrixKeypadTests() :
        keypadReader{ pins.CreateMatrixKeypadReader() },
        keypad{ &keypadReader },
        keyState{false},
        column{0},
        row{0}
    {
        fakeTime = high_resolution_clock::time_point();

        pins.columnPinChangeCallback = [this](MatrixKeypadPinsFake* pins)
        {
            if(pins->column[column]) pins->row[row] = keyState;
        };
    }

    void ChangeKeyToStateAfterXms(bool state, int ms)
    {
        keyState = state;
        fakeTime += milliseconds(ms);
        keypad.Service();
    }
};

TEST_F(MatrixKeypadTests, If_the_pins_do_not_change_state_then_no_key_is_pressed)
{
    //  Given
    bool called = false;
    keypad.SetKeyPressedCallback([&called](int key) { called = true; });
    keyState = false;

    // When
    keypad.Service();
    fakeTime += milliseconds(10);
    keypad.Service();

    // Then
    ASSERT_FALSE(called);
}



TEST_F(MatrixKeypadTests, If_a_pin_high_for_10ms_and_then_goes_low_the_corresponding_key_is_pressed)
{
    auto ASSERT_KEY_PRESSED = [this](int expectedKeyIndex)
    {
        //  Given
        fakeTime = high_resolution_clock::time_point();
        bool called = false;
        int keyIndex = 0;
        keypad.SetKeyPressedCallback([&called, &keyIndex](int key)
        {
            called = true;
            keyIndex = key;
        });

        // When
        ChangeKeyToStateAfterXms(false, 0); // 0ms
        ChangeKeyToStateAfterXms(true, 1);  // 1ms
        ChangeKeyToStateAfterXms(true, 10); // 11ms


        ASSERT_FALSE(called);

        ChangeKeyToStateAfterXms(false, 1); // 12ms

        // Then
        ASSERT_TRUE(called);
        ASSERT_EQ(expectedKeyIndex, keyIndex);
    };

    column = 0;
    row = 0;
    ASSERT_KEY_PRESSED(0);
    row = 1;
    ASSERT_KEY_PRESSED(1);
    row = 2;
    ASSERT_KEY_PRESSED(2);
    row = 3;
    ASSERT_KEY_PRESSED(3);

    column = 1;
    row = 0;
    ASSERT_KEY_PRESSED(4);
    row = 1;
    ASSERT_KEY_PRESSED(5);
    row = 2;
    ASSERT_KEY_PRESSED(6);
    row = 3;
    ASSERT_KEY_PRESSED(7);

    column = 2;
    row = 0;
    ASSERT_KEY_PRESSED(8);
    row = 1;
    ASSERT_KEY_PRESSED(9);
    row = 2;
    ASSERT_KEY_PRESSED(10);
    row = 3;
    ASSERT_KEY_PRESSED(11);
}

TEST_F(MatrixKeypadTests, If_a_pin_high_for_less_than_10ms_and_then_goes_low_the_corresponding_key_is_not_pressed)
{
    auto ASSERT_KEY_NOT_PRESSED = [this]()
    {
        //  Given
        fakeTime = high_resolution_clock::time_point();
        bool called = false;
        keypad.SetKeyPressedCallback([&called](int key)
        {
            called = true;
        });

        // When
        ChangeKeyToStateAfterXms(false, 0); // 0ms
        ChangeKeyToStateAfterXms(true, 1);  // 1ms
        ChangeKeyToStateAfterXms(true, 9);  // 10ms
        ChangeKeyToStateAfterXms(false, 1); // 11ms

        // Then
        ASSERT_FALSE(called);
    };

    column = 0;
    row = 0;
    ASSERT_KEY_NOT_PRESSED();
    row = 1;
    ASSERT_KEY_NOT_PRESSED();
    row = 2;
    ASSERT_KEY_NOT_PRESSED();
    row = 3;
    ASSERT_KEY_NOT_PRESSED();

    column = 1;
    row = 0;
    ASSERT_KEY_NOT_PRESSED();
    row = 1;
    ASSERT_KEY_NOT_PRESSED();
    row = 2;
    ASSERT_KEY_NOT_PRESSED();
    row = 3;
    ASSERT_KEY_NOT_PRESSED();

    column = 2;
    row = 0;
    ASSERT_KEY_NOT_PRESSED();
    row = 1;
    ASSERT_KEY_NOT_PRESSED();
    row = 2;
    ASSERT_KEY_NOT_PRESSED();
    row = 3;
    ASSERT_KEY_NOT_PRESSED();
}

TEST_F(MatrixKeypadTests, If_the_key_attached_to_a_pin_causes_bounce_then_the_corresponding_key_is_not_pressed)
{
    //  Given
    fakeTime = high_resolution_clock::time_point();

    column = 0;
    row = 0;
    bool called = false;
    keypad.SetKeyPressedCallback([&called](int key)
    {
        called = true;
    });

    // When
    ChangeKeyToStateAfterXms(false, 0);
    ChangeKeyToStateAfterXms(true, 1);
    ChangeKeyToStateAfterXms(true, 9);
    ChangeKeyToStateAfterXms(false, 1);
    ChangeKeyToStateAfterXms(true, 1);
    ChangeKeyToStateAfterXms(true, 9);
    ChangeKeyToStateAfterXms(false, 1);

    // Then
    ASSERT_FALSE(called);

}
