#include "AlsaMicrophoneInput.h"
#include "AnalyzeAudioSection.h"
#include <iostream>
#include <signal.h>
#include <bitset>
#include <vector>

bool continueRunning = true;

void StopLoop(int signal)
{
    // This will release the capture audio device for use
    // with other applications.
    continueRunning = false;
}

int main()
{
    continueRunning = true;
    signal(SIGINT, &StopLoop);
    int alsaErrorCode = 0;
    snd_pcm_uframes_t periodSize{1024};

    AlsaMicrophoneInput mic;
    int channels = 1;
    int sampleRate = 44100;
    int beepFrequency = 440;
    int seconds = 15;
    alsaErrorCode = mic.SetupAudioDevice("hw:1", 4096, sampleRate, channels, periodSize);

    if (alsaErrorCode < 0)
    {
        return -1;
    }
    std::vector<double> periodsVector = {0.5,1.0,3.5,4.0};

    std::cout << "Analysing audio input for " << std::to_string(seconds) << " seconds..." << std::endl;
    std::vector<double> correlationData = AnalyzeAudioCorrelation(beepFrequency,periodsVector,sampleRate,1,seconds,1024,&mic,&continueRunning,&alsaErrorCode);
    std::cout << "Audio analysis finished." << std::endl;

    double firstCorrelationRatio = correlationData[0]/correlationData[1];
    double secondCorrelationRatio = correlationData[2]/correlationData[3];

    std::cout << "Difference at 0.5: " << std::to_string(correlationData[0]) << std::endl;
    std::cout << "Difference at 1.0: " << std::to_string(correlationData[1]) << std::endl;
    std::cout << "Ratio: " << std::to_string(firstCorrelationRatio) << std::endl;

    std::cout << "Difference at 3.5: " << std::to_string(correlationData[2]) << std::endl;
    std::cout << "Difference at 4.0: " << std::to_string(correlationData[3]) << std::endl;
    std::cout << "Ratio: " << std::to_string(secondCorrelationRatio) << std::endl;

    if (firstCorrelationRatio > 5 && secondCorrelationRatio > 3)
    {
        std::cout << "Beeping detected!" << std::endl;
    } else
    {
        std::cout << "Beeping not detected." << std::endl;
    }

    return 0;

}
