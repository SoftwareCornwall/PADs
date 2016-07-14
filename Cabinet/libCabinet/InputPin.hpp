#ifndef INPUTPIN_H
#define INPUTPIN_H

class InputPin
{
public:
    virtual ~InputPin() {}
    virtual bool State() = 0;
};

#endif // INPUTPUT_H

