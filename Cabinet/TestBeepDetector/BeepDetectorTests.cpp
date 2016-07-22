#include <gtest/gtest.h>
#include <cmath>
#include "FakeMicrophoneInput.h"
#include "AnalyzeAudioSection.h"
#include "Goertzel.h"

using namespace ::testing;

bool continueRunning = true;

void StopLoop(int signal)
{
    // This will release the capture audio device for use
    // with other applications.
    continueRunning = false;
}

class BeepDetectorTests : public Test
{
public:

    BeepDetectorTests()
    {
    }

};

TEST_F(BeepDetectorTests, Read_Fake_Input_File_Samples)
{

    FakeMicrophoneInput FakeMic;

    int errorCode = 0;
    char *frameBuffer = nullptr;

    FakeMic.SetupAudioDevice("", 16384, 44100, 1, 4096);
    FakeMic.LoadAudioFile("SampleNoise0_1s.wav");
    frameBuffer = FakeMic.GetFrames(4, &errorCode);

    EXPECT_EQ(48, frameBuffer[0]);
    EXPECT_EQ(70, frameBuffer[1]);
    EXPECT_EQ(16, frameBuffer[2]);
    EXPECT_EQ(182, frameBuffer[3]);
    EXPECT_EQ(123, frameBuffer[4]);
    EXPECT_EQ(87, frameBuffer[5]);
    EXPECT_EQ(218, frameBuffer[6]);
    EXPECT_EQ(169, frameBuffer[7]);

    free(frameBuffer);

}

TEST_F(BeepDetectorTests, Read_Fake_Input_And_Process)
{

    continueRunning = true;

    signal(SIGINT, &StopLoop);

    FakeMicrophoneInput mic;

    mic.LoadAudioFile("tone-440-480.flac");

    int alsaErrorCode = 0;
    unsigned long periodSize{4096};
    int channels = 1;
    alsaErrorCode = mic.SetupAudioDevice("hw:1", 16384, 44100, channels, periodSize);

    for(int i = 0; i < 16 && continueRunning == true; i++)
    {
        char *frames = mic.GetFrames(1024, &alsaErrorCode);
        short *frames_short = reinterpret_cast<short*>(frames);
        double frequency_effect = goertzel_mag(1024 * channels, 440, 44100, frames_short);
        //std::cout << std::to_string(frequency_effect) << " " << std::string(static_cast<size_t>(frequency_effect/1024), '>') << std::endl;
        EXPECT_LE(23000, frequency_effect);
        EXPECT_GE(25000, frequency_effect);
        free(frames);
    }

}

TEST_F(BeepDetectorTests, Read_Fake_Input_And_Find_RMS)
{

    continueRunning = true;

    signal(SIGINT, &StopLoop);

    FakeMicrophoneInput mic;

    mic.LoadAudioFile("tone-440-480.flac");

    int errorCode = 0;
    unsigned long periodSize{4096};
    int channels = 1;
    errorCode = mic.SetupAudioDevice("hw:1", 16384, 44100, channels, periodSize);
    std::vector<double> periodsVector = {0.5,1.0};
    std::vector<double> correlationData = AnalyzeAudioCorrelation(440,periodsVector,44100,1,15,1024,&mic,&continueRunning,&errorCode);


    ASSERT_LE(50, correlationData[0]/correlationData[1]);
}
