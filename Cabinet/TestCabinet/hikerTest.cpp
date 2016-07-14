#include <gtest/gtest.h>

using namespace testing;
void f();

TEST (hiker,answer)
{
    FAIL();
    f();
}
