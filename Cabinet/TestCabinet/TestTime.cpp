#include "TestTime.hpp"
using namespace ::std::chrono;

high_resolution_clock::time_point fakeTime;

high_resolution_clock::time_point currentTime()
{
    return fakeTime;
}
