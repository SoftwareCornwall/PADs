#include <gtest/gtest.h>
#include "unittest.h"

int main(int argc, char *argv[]){

    ::testing::InitGoogleTest();
    int testResult = RUN_ALL_TESTS();

    return 0;

}
