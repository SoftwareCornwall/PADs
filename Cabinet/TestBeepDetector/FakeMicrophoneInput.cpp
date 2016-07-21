#include "FakeMicrophoneInput.h"
#include <iostream>

FakeMicrophoneInput::FakeMicrophoneInput()
{
    //ctor
}

FakeMicrophoneInput::~FakeMicrophoneInput()
{
    //dtor
}

int FakeMicrophoneInput::SetupAudioDevice(std::string AudioDevice, int buffer_frames, unsigned int rate, unsigned int channels, unsigned long period_size)
{
    this->AudioDevice = AudioDevice;
    this->buffer_frames = buffer_frames;
    this->rate = rate;
    this->channels = channels;
    this->period_size = period_size;

    return 0;

}

void FakeMicrophoneInput::LoadAudioFile(std::string Filename)
{

    SF_INFO audioFileInfo;
    audioFileInfo.format = 0;

    audioFile = sf_open(Filename.c_str(), SFM_READ, &audioFileInfo);

}

char* FakeMicrophoneInput::GetFrames(int numberOfFrames, int *ErrorCode)
{

    char *buffer = new char[(numberOfFrames * channels * 2)];

    short *frameBuffer = static_cast<short*>(static_cast<void*>(buffer));

    sf_count_t framesRead = sf_readf_short(audioFile, frameBuffer, numberOfFrames);

    if (framesRead < numberOfFrames)
    {
        return nullptr;
    }

    std::cout << std::to_string(framesRead) << " frames read" << std::endl;

    return buffer;

}
