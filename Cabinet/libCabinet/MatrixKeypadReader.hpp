#ifndef MATRIXKEYPADREADER_HPP
#define MATRIXKEYPADREADER_HPP

#include "InputPin.hpp"
#include "OutputPin.hpp"
#include <stdint.h>

class MatrixKeypadReader
{
private:
    OutputPin *column1;
    OutputPin *column2;
    OutputPin *column3;
    InputPin *row1;
    InputPin *row2;
    InputPin *row3;
    InputPin *row4;
public:
    MatrixKeypadReader(OutputPin *column1, OutputPin *column2,
                 OutputPin *column3, InputPin *row1,
                 InputPin *row2, InputPin *row3,
                 InputPin *row4);

    uint16_t Read() const;

private:
    uint16_t ReadColumn(OutputPin *column) const;
};

#endif // MATRIXKEYPAD_HPP
