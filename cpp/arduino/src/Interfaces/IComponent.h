#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <Arduino.h>
#include "SimpleInterfaces.h"

class IComponent : IPrintable, IInitializable
{
public:
    explicit IComponent(const int & pin_count, const byte * pins) : IComponent(pin_count)
    {
         memcpy(this->pins, pins, pin_count);
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

    void printDebug() override          // Base implementation of IPrintable
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
