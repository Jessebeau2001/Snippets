#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <Arduino.h>

class MotorDriver
{
public:
    MotorDriver(byte control_pin_A, byte control_pin_B, byte speed_pin, byte enable_pin, int default_speed = 70)
        : control_pin_A(control_pin_A), control_pin_B(control_pin_B), speed_pin(speed_pin), enable_pin(enable_pin), motor_speed(default_speed)
    {
        init();
    }

    void init() const
    {
        pinMode(control_pin_A, OUTPUT);
        pinMode(control_pin_B, OUTPUT);
        pinMode(speed_pin, OUTPUT);
        analogWrite(speed_pin, motor_speed);
        pinMode(enable_pin, OUTPUT);
        digitalWrite(enable_pin, HIGH); // Always high cuz enables motor circuit
    }

    void setSpeed(int new_speed)
    {
        motor_speed = new_speed;
        analogWrite(speed_pin, motor_speed);
    }

    void driveForward() const
    {
        digitalWrite(control_pin_A, LOW);
        digitalWrite(control_pin_B, HIGH);
    }

    void stop() const
    {
        digitalWrite(control_pin_A, LOW);
        digitalWrite(control_pin_B, LOW);
    }

private:
    byte control_pin_A, control_pin_B;
    byte speed_pin;
    byte enable_pin;

    int motor_speed = 0;
};

#endif
