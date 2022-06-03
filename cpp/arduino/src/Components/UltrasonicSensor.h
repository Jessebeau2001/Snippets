#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include "Interfaces/ISensor.h"

class UltrasonicSensor : ISensor // , public IDelayable
{
public:
    UltrasonicSensor(const byte & echo_pin, const byte & trig_pin) : ISensor(2)
    {
        pins[0] = echo_pin;
        pins[1] = trig_pin;
        ISensor::init();
        pinMode(trig_pin, OUTPUT); // Overrides input mode set int ISensor::Init()
    }

    void update() override
    {
        digitalWrite(*trig_pin(), LOW);
        delayMicroseconds(2);
        digitalWrite(*trig_pin(), HIGH);
        delayMicroseconds(10);
        auto duration = pulseIn(*echo_pin(), HIGH);
        distance = duration * 0.034 / 2;
    }

    const int & getDistance() const { return distance; }

private:
    const byte  * echo_pin() { return &pins[0]; }
    const byte * trig_pin() { return &pins[1]; }

    int distance{};
};

#endif
