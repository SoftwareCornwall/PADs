#include "MatrixKeypadReader.hpp"

MatrixKeypadReader::MatrixKeypadReader(OutputPin *column1, OutputPin *column2,
                                       OutputPin *column3, InputPin *row1,
                                       InputPin *row2, InputPin *row3,
                                       InputPin *row4) :
    column1{column1}, column2{column2}, column3{column3},
    row1{row1}, row2{row2}, row3{row3}, row4{row4}
{
}

uint16_t MatrixKeypadReader::Read() const
{
    uint16_t sum = 0;

    sum |= ReadColumn(column1) << 0;
    sum |= ReadColumn(column2) << 4;
    sum |= ReadColumn(column3) << 8;

    return sum;
}

uint16_t MatrixKeypadReader::ReadColumn(OutputPin *column) const
{
    uint16_t sum = 0;

    column->State(true);

    sum |= row1->State() ? (1 << 0) : 0;
    sum |= row2->State() ? (1 << 1) : 0;
    sum |= row3->State() ? (1 << 2) : 0;
    sum |= row4->State() ? (1 << 3) : 0;

    column->State(false);

    return sum;
}
