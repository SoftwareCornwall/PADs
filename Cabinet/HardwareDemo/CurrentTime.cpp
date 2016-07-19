#include <chrono>


using namespace std::chrono;
high_resolution_clock::time_point currentTime()
{
    return high_resolution_clock::now();
}
