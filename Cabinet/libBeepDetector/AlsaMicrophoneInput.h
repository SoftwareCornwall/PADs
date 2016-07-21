#ifndef ALSAMICROPHONEINPUT_H
#define ALSAMICROPHONEINPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <string>

#include "MicrophoneInput.h"

class AlsaMicrophoneInput : public MicrophoneInput
{
    public:
        int SetupAudioDevice(std::string AlsaAudioDevice, int buffer_frames, unsigned int rate, unsigned int channels, unsigned long period_size);
        ~AlsaMicrophoneInput();
        char* GetFrames(int numberOfFrames, int *alsaErrorCode);
    protected:
    private:
        std::string AlsaAudioDevice = "";
        snd_pcm_t *pcm_handle = nullptr;
        snd_pcm_hw_params_t *hw_params = nullptr;
        snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;
        int buffer_frames = 0;
        unsigned int channels = 0;
        unsigned int rate = 0;
        unsigned long period_size = 0;
};

#endif // ALSAMICROPHONEINPUT_H
