#include <gtest/gtest.h>
#include "CodeCheck.hpp"
#include "TestOutputPin.h"

using namespace testing;

TEST(CodeCheckTests, test_if_no_code_has_been_entered)
{

    CodeCheck checker;
    EXPECT_EQ(false, checker.inputCheck(""));
}

TEST(CodeCheckTests, test_if_incorrect_code_is_entered_returns_false)
{

    CodeCheck checker;
    EXPECT_EQ(false, checker.inputCheck("12364"));
}

TEST(CodeCheckTests, test_if_the_strings_match)
{
    CodeCheck checker;
    EXPECT_EQ(true, checker.inputCheck("1234"));
}

TEST(CodeCheckTests, test_if_key_input_is_valid_1234e)
{

    CodeCheck checker;
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(3);
    checker.keyPressed(4);
    checker.keyPressed(10);
    EXPECT_EQ("1234", checker.getCodeEntered());
}

TEST(CodeCheckTests, test_if_key_input_is_valid_12e)//e should reset code if code incorrect
{

    CodeCheck checker;
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(10);
    EXPECT_EQ("", checker.getCodeEntered());
}

TEST(CodeCheckTests, test_if_key_input_is_valid_12c)
{

    CodeCheck checker;
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(11);
    EXPECT_EQ("", checker.getCodeEntered());
}
TEST(CodeCheckTests, test_if_key_input_is_valid_12c2)
{

    CodeCheck checker;
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(11);
    checker.keyPressed(2);
    EXPECT_EQ("2", checker.getCodeEntered());
}

TEST(CodeCheckTests, test_if_key_input_is_invalid_doorPin_false_1233e)
{
    bool unlockCalled = false;

    CodeCheck checker;
    checker.SetUnlockCallback([&unlockCalled]()
    {
        unlockCalled = true;
    });
    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(3);
    checker.keyPressed(3);
    checker.keyPressed(10);
    EXPECT_FALSE(unlockCalled) << "unlock Callback was called when it wasn't expected";
}

TEST(CodeCheckTests, test_if_key_input_is_valid_doorPin_true_1234e)
{
    bool unlockCalled = false;

    CodeCheck checker;

    checker.SetUnlockCallback([&unlockCalled]()
    {
        unlockCalled = true;
    });

    checker.keyPressed(1);
    checker.keyPressed(2);
    checker.keyPressed(3);
    checker.keyPressed(4);
    checker.keyPressed(10);
    EXPECT_TRUE(unlockCalled) << "unlock Callback wasn't called";
}

