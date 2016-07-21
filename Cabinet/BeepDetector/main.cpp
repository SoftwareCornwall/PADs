#include "AlsaMicrophoneInput.h"
#include <iostream>
#include <signal.h>
#include <bitset>

bool continueRunning = true;

void StopLoop(int signal)
{
    // This will release the capture audio device for use
    // with other applications.
    continueRunning = false;
}

int main()
{

    int alsaErrorCode = 0;
    snd_pcm_uframes_t periodSize{4096};

    AlsaMicrophoneInput mic;
    int channels = 2;
    alsaErrorCode = mic.SetupAudioDevice("hw:1", 16384, 44100, channels, periodSize);

    if (alsaErrorCode < 0)
    {
        return -1;
    }

    for(int i = 0; i < 1024 && continueRunning == true; i++)
    {
        char *frames = mic.GetFrames(1024, &alsaErrorCode);
        short *frames_short = reinterpret_cast<short*>(frames);
        int averageSample = 0;

        for(int sample = 0; sample < (1024 * channels); sample += channels)
        {
            short currentSample = frames_short[sample];
            currentSample /= (65536/4096);
            averageSample += (currentSample > 0 ? currentSample : -currentSample);
        }
        averageSample /= (1024 * channels);

        std::cout << std::to_string(averageSample) << " " << std::string(static_cast<size_t>(averageSample), '>') << std::endl;

        free(frames);
    }

    return 0;

}
