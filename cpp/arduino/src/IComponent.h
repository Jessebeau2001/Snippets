#ifndef ICOMPONENT_H
#define ICOMPONENT_H

class IComponent {
public:
    explicit IComponent(const int & pin_count, const byte * pins) : IComponent(pin_count)
    {
//        for (int i = 0; i < pin_count; i++)
//        {
//            this->pins[i] = pins[i];
//        }

         memcpy(this->pins, pins, pin_count); // TODO: Consider this
    }

    explicit IComponent(const byte & pin) : IComponent(1)
    {
        pins[0] = pin;
    }

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

    virtual void printDebug()
    {
        Serial.print(" with pins: ["); Serial.print(pins[0]);
        for (int i = 1; i < pin_count; i++)
        {
            Serial.print(", "); Serial.print(pins[i]);
        }
        Serial.println("])");
    }

    byte * pins;
    int pin_count;
};

#endif
