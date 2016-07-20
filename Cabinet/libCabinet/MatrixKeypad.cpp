#include "MatrixKeypad.hpp"
#include <chrono>

MatrixKeypad::MatrixKeypad(MatrixKeypadReader *reader) :
    reader{reader}
{
    for(bool &state : previousState)
    {
        state = false;
    }
}

void MatrixKeypad::SetKeyPressedCallback(key_pressed_callback_t callback)
{
    keyPressedCallback = callback;
}

void MatrixKeypad::Service()
{
    uint16_t states = reader->Read();
    time_point_t now = CurrentTime();

    for(size_t key = 0; key < numberOfKeys; key++)
    {
        const bool state = states & (1 << key);

        if(state && !previousState[key])
        {
            pressedStartTime[key] = now;
        }

        if(!state && previousState[key])
        {
            auto timePressed = now - pressedStartTime[key];
            if(timePressed > std::chrono::milliseconds{10})
            {
                if(keyPressedCallback)
                    keyPressedCallback(static_cast<int>(key));
            }
        }

        previousState[key] = state;
    }
}
