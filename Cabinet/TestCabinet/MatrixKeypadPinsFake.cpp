#include "MatrixKeypadPinsFake.hpp"

MatrixKeypadPinsFake::ColumnPin::ColumnPin(MatrixKeypadPinsFake *matrix, bool *columnState) :
    matrix{matrix},
    columnState{columnState}
{
    *columnState = false;
}

void MatrixKeypadPinsFake::ColumnPin::State(bool state)
{
    *columnState = state;
    matrix->ColumnPinChange();
}

MatrixKeypadPinsFake::RowPin::RowPin(bool *rowState) :
    rowState{rowState}
{
    *rowState = false;
}

bool MatrixKeypadPinsFake::RowPin::State()
{
    return *rowState;
}

MatrixKeypadPinsFake::MatrixKeypadPinsFake() :
    columnPin{ ColumnPin{this, &column[0]}, ColumnPin{this, &column[1]}, ColumnPin{this, &column[2]} },
    rowPin{ RowPin{&row[0]}, RowPin{&row[1]}, RowPin{&row[2]}, RowPin{&row[3]} }
{
}

void MatrixKeypadPinsFake::ColumnPinChange()
{
    for(bool & b : row)
    {
        b = false;
    }

    columnPinChangeCallback(this);
}

MatrixKeypadReader MatrixKeypadPinsFake::CreateMatrixKeypadReader()
{
    return MatrixKeypadReader{ &columnPin[0], &columnPin[1], &columnPin[2],
                &rowPin[0], &rowPin[1], &rowPin[2], &rowPin[3]};
}
