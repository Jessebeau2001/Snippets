#include <Arduino.h>
#include "../.pio/libdeps/uno/Servo/src/Servo.h"
#include "TrackSensor.h"
#include "MotorController.h"

byte sensor_pins[5] = { A0, A2, A3, A4, A5 };
TrackSensor tracker = TrackSensor(5, sensor_pins);
Servo steer;
MotorController motor = MotorController(4, 7, 6, A1, 70, true);

int steer_angle = 0;
float steer_mod = 1.4;

void setup()
{
    Serial.begin(9600);

    tracker.printDebug();
    motor.printDebug();

    steer.attach(9);
}

void loop()
{
    steer_angle = tracker.getAngle();

    if (tracker.getState() == TrackSensor::LOST)
    {
        motor.brake();
    } else {
        motor.driveForward();
        steer.write(90 + steer_angle * steer_mod); // NOLINT(cppcoreguidelines-narrowing-conversions)
    }
}
