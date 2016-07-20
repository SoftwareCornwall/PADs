#include "AlsaMicrophoneInput.h"
#include <iostream>

using namespace std;

AlsaMicrophoneInput::AlsaMicrophoneInput(std::string AlsaAudioDevice, int buffer_frames, unsigned int rate, unsigned int channels, unsigned long period_size, int *alsaErrorCode) :
    AlsaAudioDevice(AlsaAudioDevice), buffer_frames(buffer_frames), channels(channels), rate(rate), period_size(period_size)
{

    (*alsaErrorCode) = 0;
    snd_pcm_uframes_t period_size_frames = period_size;

    if (((*alsaErrorCode) = snd_pcm_open(&pcm_handle, AlsaAudioDevice.c_str(), SND_PCM_STREAM_CAPTURE, 0)) < 0)
    {
        std::cerr << "Unable to open audio device \"" << AlsaAudioDevice
        << "\":" << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Audio interface \"" << AlsaAudioDevice << "\" opened" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_hw_params_malloc (&hw_params)) < 0)
    {
        std::cerr << "Unable to allocate hardware parameter structure for \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Hardware parameter structure allocated" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_hw_params_any (pcm_handle, hw_params)) < 0)
    {
        std::cerr << "Cannot initialise hardware parameter structure for \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Hardware parameter structure initialised" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_hw_params_set_access (pcm_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
        std::cerr << "Cannot set access type for \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Hardware parameter access set" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_hw_params_set_format (pcm_handle, hw_params, format)) < 0)
    {
        std::cerr << "Cannot set sample format for \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Sample format set" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_hw_params_set_rate_near (pcm_handle, hw_params, &rate, 0)) < 0)
    {
        std::cerr << "Cannot set sample rate for \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Sample rate set" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_hw_params_set_period_size_near(pcm_handle, hw_params, &period_size_frames, 0)) < 0)
    {
        std::cerr << "Cannot set period size for \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Period size set" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_hw_params_set_channels (pcm_handle, hw_params, channels)) < 0)
    {
        std::cerr << "Cannot set channel count for \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Channel count set" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_hw_params (pcm_handle, hw_params)) < 0)
    {
        std::cerr << "Cannot set parameters for \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Hardware parameters set" << std::endl;

    snd_pcm_hw_params_free (hw_params);

    std::cout << "Hardware parameters allocated memory freed" << std::endl;

    if (((*alsaErrorCode) = snd_pcm_prepare (pcm_handle)) < 0)
    {
        std::cerr << "Cannot prepare audio interface \"" << AlsaAudioDevice
        << "\" for capture: " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return;
    }

    std::cout << "Audio interface prepared for capture" << std::endl;

}

char* AlsaMicrophoneInput::GetFrames(int numberOfFrames, int *alsaErrorCode)
{

    char *frameBuffer = nullptr;

    int attempts = 0;
    snd_pcm_uframes_t availableFrames = -1;

    while (attempts < 10000 && numberOfFrames <= (int)availableFrames)
    {

        availableFrames = snd_pcm_avail(pcm_handle);
        attempts++;

    }

    if (attempts >= 10000)
    {

        return nullptr;

    }

    frameBuffer = (char *)malloc(numberOfFrames * (snd_pcm_format_width(format) / 8) * channels);

    if (((*alsaErrorCode) = snd_pcm_readi(pcm_handle, frameBuffer, numberOfFrames)) < 0)
    {

        std::cerr << "Cannot read frames from audio interface \"" << AlsaAudioDevice
        << "\": " << (std::string)snd_strerror((*alsaErrorCode)) << std::endl;
        return nullptr;

    }

    return frameBuffer;

}

AlsaMicrophoneInput::~AlsaMicrophoneInput()
{

    // Close the microphone input and free the buffer.

    if (pcm_handle != nullptr)
    {
        snd_pcm_drain(pcm_handle);
        snd_pcm_close(pcm_handle);
        std::cout << "Audio Interface \"" << AlsaAudioDevice << "\" closed\n";
    }

}
