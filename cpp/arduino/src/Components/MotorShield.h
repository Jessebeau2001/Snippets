#ifndef MOTORSHIELD_H
#define MOTORSHIELD_H

#include "Interfaces/IActuator.h"

/*
 * The pins for motorControl driver we are using are:
 * Driver 1: Control Pins (7 & 8), PWM Speed pin (5), Enable pin (A0)
 * Driver 2: Control Pins (4 & 9), PWM Speed pin (6), Enable pin (A1)
 */

class MotorShield : public IActuator
{
public:
    MotorShield(byte pin_a, byte pin_b, byte pin_speed, byte pin_enable, // Calls constructor in IComponent
        int default_speed = 70, bool enabled = false) : IActuator(4)
    {
        pins[0] = pin_a;
        pins[1] = pin_b;
        pins[2] = pin_speed;
        pins[3] = pin_enable;
        IActuator::init();
        setSpeed(default_speed);
        setEnable(enabled);
    }

    void driveForward()
    {
        digitalWrite(*pin_a(), LOW);
        digitalWrite(*pin_b(), HIGH);
    }

    void brake()
    {
        digitalWrite(*pin_a(), LOW);
        digitalWrite(*pin_b(), LOW);
    }

    void reverse()
    {
        digitalWrite(*pin_a(), HIGH);
        digitalWrite(*pin_b(), LOW);
    }

    void setSpeed(const int & new_speed)
    {
        current_speed = new_speed;
        analogWrite(*pin_speed(), new_speed);
    }

    void setEnable(const bool & enable)
    {
        enabled = enable;
        digitalWrite(*pin_enable(), enable);
    }

    void printDebug() override
    {
        Serial.print("Pin A: "); Serial.print(*pin_a());
        Serial.print(", pin B: "); Serial.print(*pin_b());
        Serial.print(", speed dial pin: "); Serial.print(*pin_speed());
        Serial.print(", enable pin: "); Serial.print(*pin_enable());
        Serial.print(", motorControl is "); Serial.print(enabled ? "enabled" : "disabled");
        Serial.print(" & speed is set to: "); Serial.println(current_speed);
    }

private:
    byte * pin_a() { return &pins[0]; }         // These can also be references
    byte * pin_b() { return &pins[1]; }         // but I think pointers make more
    byte * pin_speed() { return &pins[2]; }     // sense in this context
    byte * pin_enable() { return &pins[3]; }

    int current_speed{};
    bool enabled{};
};

#endif
