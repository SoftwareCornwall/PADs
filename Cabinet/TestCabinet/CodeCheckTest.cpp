#include <gtest/gtest.h>
#include "CodeCheck.hpp"

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
