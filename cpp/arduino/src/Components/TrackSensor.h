#ifndef TRACKSENSOR_H
#define TRACKSENSOR_H

#include "Interfaces/ISensor.h"
#include "vec2.h"
#include <Arduino.h>

class TrackSensor : public ISensor
{
public:
    TrackSensor(const int & pin_count, const byte * pins, const int & threshold = 100) : ISensor(pin_count, pins)
    {
        this->threshold = threshold;
        center_pin_pos = pin_count / 2;
        center_pin = &pins[center_pin_pos];
    }

    void printDebug() override
    {
        ISensor::printDebug();
        Serial.print("^^^ Center pin pos: "); Serial.print(center_pin_pos);
        Serial.print(" gives center pin: "); Serial.println(*center_pin);
    }

    void printSegments() const
    {
        for (int i = 0; i < pin_count; i++)
        {
            Serial.print(lineFound(pins[i]) ? "| # " : "| . ");
        }
        Serial.print("| Angle: "); Serial.println(angle);
    }

    int getAngle()
    {
        update();
        return angle;
    }

    enum Line { LEFT, MIDDLE, RIGHT, LOST, ALL };

    const Line & getState() const
    {
        return state;
    }

protected:
    int threshold = 0;
    int center_pin_pos;
    int angle = 0;

    const byte * center_pin;
    vec2 vector{};
    Line state = LOST;

    void update() override
    {
        vector.zero();
        int all_on = 0;
        for (int i = 0; i < pin_count; i++)
        {
            if (lineFound(pins[i]))
            {
                vector += vec2(i - center_pin_pos, 5); // NOLINT(cppcoreguidelines-narrowing-conversions)
                all_on++; // TODO: This is dog shit
            }
        }

        if (vector.isZero())
        {
            state = LOST;
            angle = 0;
            return;
        }

        vector.normalize();
        angle = vec2(-1, 0).angle(vector) - 90; // NOLINT(cppcoreguidelines-narrowing-conversions)

        if (angle != 0) {
            if (angle < 0) state = LEFT;
            else state = RIGHT;
        }
        else state = MIDDLE;

        if (all_on == pin_count)
        {
            state = ALL;
        }
    }

    // Pin IS pin, not index
    virtual bool lineFound(const byte & pin) const
    {
        return analogRead(pin) < threshold;
    }
};

class TrackSensor_Digital : public TrackSensor
{
public:
    using TrackSensor::TrackSensor;

protected:
    // Because of our beautiful code structure we only need to overload 1 method to make the whole thing rely on digital
    bool lineFound(const byte & pin) const override
    {
        return !digitalRead(pin);
    }
};

#endif
