#ifndef ISENSOR_H
#define ISENSOR_H

#include <Arduino.h>
#include "IComponent.h"

//template <typename T> // Maybe this eventually
class ISensor : public IComponent
{
public:
    ISensor(const int & pin_count, const byte * pins) : IComponent(pin_count, pins)
    {
        init();
    }

    void printDebug() override
    {
        Serial.print("(Sensor with pins: [");
        Serial.print(pins[0]);
        for (int i = 1; i < pin_count; i++)
        {
            Serial.print(", ");
            Serial.print(pins[i]);
        }
        Serial.println("])");
    }

protected:
    void init() override
    {
        Serial.println("Setting up Sensor");
        for (int i = 0; i < pin_count; i++)
        {
            pinMode(pins[i], INPUT);
        }
    }

    virtual void update() = 0;
};

#endif
