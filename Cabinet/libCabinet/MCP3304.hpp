#ifndef MCP3304_HPP
#define MCP3304_HPP

#include "OutputPin.hpp"

class MCP3304
{
private:
    int channel;
    OutputPin *csPin;
public:
    MCP3304(int channel, int speed, OutputPin *csPin);

    int Read();
};

#endif
