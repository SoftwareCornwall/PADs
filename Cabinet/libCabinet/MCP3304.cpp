#include "MCP3304.hpp"
#include <wiringPiSPI.h>

MCP3304::MCP3304(int channel, int speed, OutputPin *csPin) :
    channel{channel},
    csPin{csPin}
{
    wiringPiSPISetup(channel, speed);
    csPin.State(true);
}

int MCP3304::Read()
{
    char command[3] = {0};
    command[0] = 0xC0;

    csPin.State(false);

    wiringPiSPIDataRW(channel, command, sizeof(command));

    csPin.State(true);

    int result = command[1];
    result <<= 8;
    result |= command[2];

    return result;
}
