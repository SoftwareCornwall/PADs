#ifndef MATRIXKEYPAD_HPP
#define MATRIXKEYPAD_HPP

#include "MatrixKeypadReader.hpp"
#include "CurrentTime.hpp"
#include <functional>

class MatrixKeypad
{
public:
    using key_pressed_callback_t = std::function<void(int)>;
    using time_point_t = decltype(CurrentTime());

    static const size_t numberOfKeys{12};
private:
    MatrixKeypadReader *reader;
    key_pressed_callback_t keyPressedCallback;

    bool previousState[numberOfKeys];
    time_point_t pressedStartTime[numberOfKeys];
public:
    MatrixKeypad(MatrixKeypadReader *reader);

    void SetKeyPressedCallback(key_pressed_callback_t callback);

    void Service();
};

#endif // MATRIXKEYPAD_HPP
