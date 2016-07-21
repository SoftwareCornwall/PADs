#ifndef FAKEMICROPHONEINPUT_H
#define FAKEMICROPHONEINPUT_H

#include "MicrophoneInput.h"
#include <string>
#include <sndfile.h>

class FakeMicrophoneInput : public MicrophoneInput
{
    public:
        FakeMicrophoneInput();
        void LoadAudioFile(std::string Filename);
        char* GetFrames(int numberOfFrames, int *ErrorCode);
        int SetupAudioDevice(std::string AudioDevice, int buffer_frames, unsigned int rate, unsigned int channels, unsigned long period_size);
        virtual ~FakeMicrophoneInput();
    protected:
    private:
        std::string AudioDevice = "";
        int buffer_frames = 0;
        unsigned int rate = 0;
        unsigned int channels = 0;
        unsigned long period_size = 0;
        SNDFILE *audioFile = nullptr;
};

#endif // FAKEMICROPHONEINPUT_H
