#include "HBridgeLock.hpp"

using namespace ::std::chrono;

HBridgeLock::HBridgeLock(OutputPin *openPin, OutputPin *closePin) :
    openPin{openPin},
    closePin{closePin},
    lockRequested{false},
    lockInProgress{false},
    unlockRequested{false},
    unlockInProgress{false}
{
    openPin->State(false);
    closePin->State(false);
}

void HBridgeLock::Lock()
{
    if(!unlockRequested && !unlockInProgress)
    {
        lockRequested = true;
    }
}

void HBridgeLock::Unlock()
{
    if(!lockRequested && !lockInProgress)
    {
        unlockRequested = true;
    }
}

void RunRequest(bool &requested, bool &inProgress,
                HBridgeLock::current_time_point_t &startTime,
                OutputPin *pin)
{
    if(requested)
    {
        requested = false;
        inProgress = true;
        startTime = currentTime();
        pin->State(true);
    }

    if(inProgress && (currentTime() - startTime) >= milliseconds(500))
    {
        inProgress = false;
        pin->State(false);
    }
}

void HBridgeLock::Service()
{
    RunRequest(lockRequested, lockInProgress, lockStartTime, closePin);
    RunRequest(unlockRequested, unlockInProgress, unlockStartTime, openPin);
}
