#ifndef ICOMPONENT_H
#define ICOMPONENT_H

class IComponent {
public:
    explicit IComponent(const int & pin_count, const byte * pins) : IComponent(pin_count)
    {
        for (int i = 0; i < pin_count; i++)
            this->pins[i] = pins[i];    // TODO: Take a look at memcpy
    }

    //TODO: Add constructor for something with 1 pin, so no variadic arguments to be handled there

    ~IComponent()
    {
        delete[] pins;
    }

protected:
    explicit IComponent(const int & pin_count)
    {
        this->pin_count = pin_count;
        this->pins = new byte[pin_count];
    }

    virtual void init() = 0;
    virtual void printDebug() = 0;

    byte * pins;
    int pin_count;
};
#endif
