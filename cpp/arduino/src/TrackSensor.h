#ifndef TRACKSENSOR_H
#define TRACKSENSOR_H

#include "ISensor.h"
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

    void printSegments()
    {
        for (int i = 0; i < pin_count; i++)
        {
            Serial.print(lineFound(pins[i]) ? "| # " : "| . ");
//            Serial.print("| ");
//            Serial.print(analogRead(pins[i]));
        }
        Serial.println("|");
    }

    int getSteerAngle()
    {
        update();
        return angle;
    }

    enum Line { START, LEFT, MIDDLE, RIGHT, LOST };

    const Line & getState()
    {
        if (angle != 0) {
            if (angle < 0) state = LEFT;
            else state = RIGHT;
        }
        else state = MIDDLE;
        return state;
    }

private:
    int threshold = 0;
    int center_pin_pos;
    int angle = 0;

    const byte * center_pin;
    vec2 vector{};
    Line state = START;

    void update() override
    {
        vector.zero();
        for (int i = 0; i < pin_count; i++)
        {
            if (lineFound(pins[i])) vector += vec2(i - center_pin_pos, 5);
        }

        if (vector.isZero()) return;

        vector.normalize();
        angle = vec2(-1, 0).angle(vector) - 90;
    }

    // Pin IS pin, not index
    bool lineFound(const byte & pin) const
    {
        return analogRead(pin) < threshold;
    }
};

#endif