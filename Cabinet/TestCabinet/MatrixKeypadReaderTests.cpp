#include "MatrixKeypadReader.hpp"
#include <gtest/gtest.h>
#include "MatrixKeypadPinsFake.hpp"

using namespace ::testing;

class MatrixKeypadReaderTests : public Test
{
public:
    MatrixKeypadPinsFake pins;
    MatrixKeypadReader keypad;

    MatrixKeypadReaderTests() :
        keypad{ pins.CreateMatrixKeypadReader() }
    {
    }
};

TEST_F(MatrixKeypadReaderTests, The_bit_matching_the_button_is_set_when_the_button_is_pressed)
{
    int columnPin = 0;
    int rowPin = 0;

    pins.columnPinChangeCallback = [&columnPin, &rowPin](MatrixKeypadPinsFake* pins)
        { if(pins->column[columnPin]) pins->row[rowPin] = true; };

    // First column
    columnPin = 0;
    rowPin = 0;
    EXPECT_EQ(0x0001, keypad.Read());

    rowPin = 1;
    EXPECT_EQ(0x0002, keypad.Read());

    rowPin = 2;
    EXPECT_EQ(0x0004, keypad.Read());

    rowPin = 3;
    EXPECT_EQ(0x0008, keypad.Read());

    // Second column
    columnPin = 1;
    rowPin = 0;
    EXPECT_EQ(0x0010, keypad.Read());

    rowPin = 1;
    EXPECT_EQ(0x0020, keypad.Read());

    rowPin = 2;
    EXPECT_EQ(0x0040, keypad.Read());

    rowPin = 3;
    EXPECT_EQ(0x0080, keypad.Read());

    // Third column
    columnPin = 2;
    rowPin = 0;
    EXPECT_EQ(0x0100, keypad.Read());

    rowPin = 1;
    EXPECT_EQ(0x0200, keypad.Read());

    rowPin = 2;
    EXPECT_EQ(0x0400, keypad.Read());

    rowPin = 3;
    EXPECT_EQ(0x0800, keypad.Read());
}
