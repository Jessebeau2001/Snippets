#ifndef POTMETER_H
#define POTMETER_H

#include "Interfaces/ISensor.h"

class PotMeter : ISensor
{
private:
    uint16_t reading = 0;

public:
    explicit PotMeter(const byte & pin) : ISensor(pin) { }

    inline const uint16_t & value()
    {
        update();
        return reading;
    }

    uint16_t value(const uint8_t & map_max)
    {
        return map(value(), 0, 1023, 0, map_max);
    }

    void printDebug() override
    {
        Serial.print("Potmeter with pin: ");
        Serial.print(pins[0]);
        Serial.print(", value: ");
        Serial.print(reading);
    }

protected:
    void update() override
    {
        reading = analogRead(pins[0]);
    }
};

#endif
