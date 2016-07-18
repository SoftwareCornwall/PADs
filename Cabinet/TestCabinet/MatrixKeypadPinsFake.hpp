#ifndef MATRIXKEYPADPINSFAKE_HPP
#define MATRIXKEYPADPINSFAKE_HPP

#include "MatrixKeypadReader.hpp"
#include "OutputPin.hpp"
#include "InputPin.hpp"
#include <functional>

class MatrixKeypadPinsFake
{
private:
    class ColumnPin : public OutputPin
    {
    private:
        MatrixKeypadPinsFake *matrix;
        bool *columnState;
    public:
        ColumnPin(MatrixKeypadPinsFake *matrix, bool *columnState);
        void State(bool state) override;
    };

    class RowPin : public InputPin
    {
    private:
        bool *rowState;
    public:
        RowPin(bool *rowState);
        bool State() override;
    };

    void ColumnPinChange();
public:
    bool column[3];
    bool row[4];

    ColumnPin columnPin[3];
    RowPin rowPin[4];
    std::function<void(MatrixKeypadPinsFake*)> columnPinChangeCallback;

    MatrixKeypadPinsFake();

    MatrixKeypadReader CreateMatrixKeypadReader();
};


#endif // MATRIXKEYPADPINSFAKE_HPP
