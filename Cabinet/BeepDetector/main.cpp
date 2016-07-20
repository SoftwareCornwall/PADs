#include "AlsaMicrophoneInput.h"

int main()
{

    int alsaErrorCode;
    snd_pcm_uframes_t periodSize{64};

    AlsaMicrophoneInput mic("hw:1", 128, 44100, 2, periodSize, &alsaErrorCode);

    if (alsaErrorCode < 0)
    {
        return -1;
    }

    return 0;

}
