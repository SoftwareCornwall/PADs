#ifndef HBRIDGELOCK_HPP
#define HBRIDGELOCK_HPP

#include "OutputPin.hpp"
#include "CurrentTime.hpp"

class HBridgeLock
{
public:
    using current_time_point_t = decltype(CurrentTime());
private:
    OutputPin *openPin;
    OutputPin *closePin;

    bool lockRequested;
    bool lockInProgress;
    current_time_point_t lockStartTime;

    bool unlockRequested;
    bool unlockInProgress;
    current_time_point_t unlockStartTime;
public:
    HBridgeLock(OutputPin *openPin, OutputPin *closePin);
    void Lock();
    void Unlock();
    void Service();
};

#endif // HBRIDGELOCK_HPP
