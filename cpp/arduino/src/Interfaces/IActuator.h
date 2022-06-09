#ifndef IACTUATOR_H
#define IACTUATOR_H

#include "IComponent.h"

class IActuator : public IComponent
{
public:
    IActuator(const int & pin_count, const byte * pins) : IComponent(pin_count, pins)
    {
        ::init();
    }

protected:
    using IComponent::IComponent;   // Grants access to IComponent(const int & pin_count)

    void init() override            // Implementation of IInitializable (src in IComponent)
    {
        for (int i = 0; i < pin_count; i++)
        {
            pinMode(pins[i], OUTPUT);
        }
    }

    void printDebug() override
    {
        Serial.print("Actuator");
        IComponent::printDebug();
    }
};

#endif
