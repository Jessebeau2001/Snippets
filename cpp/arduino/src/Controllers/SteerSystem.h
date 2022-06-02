#ifndef STEERSYSTEM_H
#define STEERSYSTEM_H

#include "Interfaces/SimpleInterfaces.h"
#include "../../.pio/libdeps/uno/Servo/src/Servo.h"
#include "Components/TrackSensor.h"

class SteerSystem : IUpdatable, IInitializable, IPrintable
{
private:
    TrackSensor * line_sensor;  // TODO: Consider making these const, or make the pointers in motorcontroller variable
    Servo * steer_wheel;

    int servo_pin;

    float angle_modifier = 1.4f;    // Steer intensity, mods the steer angle returned from TrackSensor.
    int angle_current = 0;          // Value representing current servo angle.
    int angle_offset = 90;          // Value where servo is centered.

public:
    SteerSystem(TrackSensor * sensor, Servo * steer, const int & servo_pin)
        : line_sensor(sensor), steer_wheel(steer), servo_pin(servo_pin) { }

    void init() override
    {
        if (!steer_wheel->attached())       // Don't do this in constructor, Servo library doesn't like that
            steer_wheel->attach(servo_pin);
    }

    void update() override
    {
        angle_current = (int) ((float) angle_offset + (float) line_sensor->getAngle() * angle_modifier);
        if (line_sensor->getState() == TrackSensor::LOST) return; // Remember angle when going around corner
        steer_wheel->write(angle_current + 4);
    }

    void printDebug() override
    {
        Serial.println("Steer system: ");
        Serial.println("> Steer servo: vvv");
        Serial.print("Servo is attached to pin: "); Serial.println(servo_pin);
        Serial.println("> Line sensor: vvv"); line_sensor->printDebug();
    }

    void setMod(const float & modifier) { angle_modifier = modifier; }
    const float & getMod() const { return angle_modifier; }
};

#endif
