#include "AlsaMicrophoneInput.h"
#include <iostream>
#include <signal.h>

bool continueRunning = true;

void StopLoop(int signal)
{
    std::cout << "Signal to interrupt!" << std::endl;
    continueRunning = false;
}

int main()
{

    signal(SIGINT, &StopLoop);

    int alsaErrorCode = 0;
    snd_pcm_uframes_t periodSize{4096};

    AlsaMicrophoneInput mic;
    alsaErrorCode = mic.SetupAudioDevice("hw:1", 16384, 44100, 2, periodSize);

    if (alsaErrorCode < 0)
    {
        return -1;
    }

    for(int i = 0; i < 512 && continueRunning == true; i++)
    {
        char *frames = mic.GetFrames(1024, &alsaErrorCode);
        int averageFrame = 0;

        for(int sample = 0; sample < 2048; sample++)
        {
            short currentFrame = static_cast<short>(frames[sample]);
            currentFrame = currentFrame | (static_cast<short>(frames[sample + 1]) << 8);
            currentFrame /= (65536/64);
            averageFrame += (currentFrame > 0 ? currentFrame : -currentFrame);

        }
        averageFrame /= 2048;

        std::cout << std::string(static_cast<size_t>(averageFrame), '>') << std::endl;

        free(frames);
    }



    return 0;

}
