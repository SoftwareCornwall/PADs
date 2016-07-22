#ifndef ANALYZEAUDIOSECTION_H_INCLUDED
#define ANALYZEAUDIOSECTION_H_INCLUDED

#include "MicrophoneInput.h"
#include <vector>

std::vector<double> AnalyzeAudioCorrelation(int frequency, std::vector<double> periods, int sampleRate, int channels,
                                       int durationSeconds, int chunkLength, MicrophoneInput *mic,
                                       bool *continueRunning, int *errorCode);
#endif // ANALYZEAUDIOSECTION_H_INCLUDED
