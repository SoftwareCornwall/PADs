#include <gtest/gtest.h>
#include "CodeCheck.hpp"
#include "TestOutputPin.h"

using namespace testing;

TEST(CodeCheckTests, test_if_no_code_has_been_entered)
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    EXPECT_EQ(false, checker.inputCheck(""));
}

TEST(CodeCheckTests, test_if_incorrect_code_is_entered_returns_false)
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    EXPECT_EQ(false, checker.inputCheck("12364"));
}

TEST(CodeCheckTests, test_if_the_strings_match)
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    EXPECT_EQ(true, checker.inputCheck("1234"));
}

TEST(CodeCheckTests, test_if_key_input_is_valid_1234e)
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(3);
    checker.keyPressed(4);
    checker.keyPressed(10);
    EXPECT_EQ("1234", checker.getCodeEntered());
}

TEST(CodeCheckTests, test_if_key_input_is_valid_12e)//e should reset code if code incorrect
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(10);
    EXPECT_EQ("", checker.getCodeEntered());
}

TEST(CodeCheckTests, test_if_key_input_is_valid_12c)
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(11);
    EXPECT_EQ("", checker.getCodeEntered());
}
TEST(CodeCheckTests, test_if_key_input_is_valid_12c2)
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(11);
    checker.keyPressed(2);
    EXPECT_EQ("2", checker.getCodeEntered());
}

TEST(CodeCheckTests, test_if_key_input_is_invalid_doorPin_false_1233e)
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(3);
    checker.keyPressed(3);
    checker.keyPressed(10);
    EXPECT_EQ(false, checker.getPinState());
}

TEST(CodeCheckTests, test_if_key_input_is_valid_doorPin_true_1234e)
{
    TestOutputPin pin;
    CodeCheck checker(&pin);
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(3);
    checker.keyPressed(4);
    checker.keyPressed(10);
    EXPECT_EQ(true, checker.getPinState());
}

