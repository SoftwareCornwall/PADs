#include <chrono>


using namespace std::chrono;
high_resolution_clock::time_point CurrentTime()
{
    return high_resolution_clock::now();
}
