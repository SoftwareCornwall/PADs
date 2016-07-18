#ifndef OUTPUTPIN_HPP
#define OUTPUTPIN_HPP

class OutputPin
{
public:
    virtual ~OutputPin() { };
    virtual void State(bool state) = 0;
    virtual bool getState() {return pinState;};

protected:
    bool pinState = false;

};

#endif // OUTPUTPIN_HPP
