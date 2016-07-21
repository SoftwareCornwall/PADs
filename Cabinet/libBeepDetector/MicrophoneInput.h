#ifndef MICROPHONEINPUT_H
#define MICROPHONEINPUT_H


class MicrophoneInput
{
    public:
        virtual int SetupAudioDevice(std::string AudioDevice, int buffer_frames, unsigned int rate, unsigned int channels, unsigned long period_size) = 0;
        virtual ~MicrophoneInput() {};
        virtual char* GetFrames(int numberOfFrames, int *ErrorCode) = 0;
    protected:
    private:
};

#endif // MICROPHONEINPUT_H
