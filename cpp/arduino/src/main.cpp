#include <Arduino.h>
#include "Controllers/SteerSystem.h"
#include "Controllers/MotorController.h"

//byte tracker_pins[5] = { 2, 3, 11, 12, 13 };
byte tracker_pins[5] = { 13, 12, 11, 3, 2 };
TrackSensor_Digital tracker = TrackSensor_Digital(5, tracker_pins);
Servo steer_servo;
SteerSystem steerSystem = SteerSystem(&tracker, &steer_servo, 10);

MotorShield shield = MotorShield(4, 9, 6, A1, 55, true); // Motor B
Accelerometer accel = Accelerometer(0x68, 12, 100);
MotorController motorControl = MotorController(&shield, &accel);

int want_climb = 0;

void setup()
{
    Serial.begin(9600);

    steerSystem.init();
    accel.init();
    motorControl.init();
    motorControl.setState(MotorController::DRIVE);
}

void updateMotorState()
{
    MotorController::motorState new_state;
    auto track_state = tracker.getState();
    auto accel_pitch = accel.getPitchAlt();

    if (accel_pitch > -20 && accel_pitch < 20)
    {
        if(track_state == TrackSensor::MIDDLE)
            new_state = MotorController::DRIVE;
        else
            new_state = MotorController::TURN;

        want_climb--;
    } else {
        want_climb++;
        if (want_climb > 10)
            new_state = MotorController::CLIMB;
    }

    want_climb = constrain(want_climb, 0, 15);

    motorControl.setState(new_state);
}

void loop()
{
    accel.update();
    steerSystem.update();
    updateMotorState();
    motorControl.update();
    Serial.print(" \tAngle: "); Serial.println(accel.getPitchAlt());
}
