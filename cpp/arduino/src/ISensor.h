#ifndef ISENSOR_H
#define ISENSOR_H

#include <Arduino.h>
#include "IComponent.h"

class ISensor : public IComponent
{
public:
    ISensor(const int & pin_count, const byte * pins) : IComponent(pin_count, pins)
    {
        ::init(); // If things don't work any more remove '::'
    }

    void printDebug() override
    {
        Serial.print("(Sensor");
        IComponent::printDebug();
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
