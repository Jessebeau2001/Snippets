#ifndef ISENSOR_H
#define ISENSOR_H

#include <Arduino.h>
#include "Interfaces/IComponent.h"

class ISensor : public IComponent, IUpdatable
{
public:
    ISensor(const int & pin_count, const byte * pins) : IComponent(pin_count, pins)
    {
        ::init();
    }

    void printDebug() override
    {
        Serial.print("(Sensor");
        IComponent::printDebug();
    }

protected:
    using IComponent::IComponent; // Grant accesses to single argument constructor for overlaying classes

    void init() override
    {
        Serial.println("Setting up Sensor");
        for (int i = 0; i < pin_count; i++)
        {
            pinMode(pins[i], INPUT);
        }
    }
};

#endif
