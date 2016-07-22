#include "AnalyzeAudioSection.h"
#include "Goertzel.h"
#include "autocorrelation.h"

using namespace std;

vector<double> AnalyzeAudioCorrelation(int frequency, vector<double> periods, int sampleRate, int channels,
                                       int durationSeconds, int chunkLength, MicrophoneInput *mic,
                                       bool *continueRunning, int *errorCode)
{

    vector<double> magnitudeVector;
    int chunksPerSecond = (sampleRate/chunkLength);
    int chunksToAnalyse = durationSeconds * chunksPerSecond;
    for(int i = 0; i < chunksToAnalyse && (*continueRunning) == true; i++)
    {
        char *frames = mic->GetFrames(chunkLength, errorCode);
        short *frames_short = reinterpret_cast<short*>(frames);

        double frequency_effect = goertzel_mag(chunkLength * channels, frequency, sampleRate, frames_short);
        magnitudeVector.push_back(frequency_effect);
        //cout << to_string(frequency_effect) << " " << string(static_cast<size_t>(frequency_effect/1024), '>') << endl;


        free(frames);
    }

    vector<double> correlations;
    for (size_t periodSeek = 0; periodSeek < periods.size(); periodSeek++)
    {
        correlations.push_back(AutocorrelationRMS(static_cast<int>(chunksPerSecond * periods[periodSeek]), &magnitudeVector));
    }

    return correlations;

}
