#ifndef OUTPUTPIN_HPP
#define OUTPUTPIN_HPP

class OutputPin
{
public:
    virtual ~OutputPin() { };
    virtual void State(bool state) = 0;
};

#endif // OUTPUTPIN_HPP
