#include <Arduino.h>
#include "Controllers/SteerSystem.h"
#include "Controllers/MotorController.h"
#include "Components/UltrasonicSensor.h"

byte tracker_pins[5] = { 13, 12, 11, 3, 2 };
TrackSensor_Digital tracker = TrackSensor_Digital(5, tracker_pins);
Servo steer_servo;
SteerSystem steerSystem = SteerSystem(&tracker, &steer_servo, 10);

MotorShield shield = MotorShield(4, 9, 6, A1, 55, true); // Motor B
Accelerometer accel = Accelerometer(0x68, 12, 100);
MotorController motorControl = MotorController(&shield, &accel);

UltrasonicSensor dist_sensor = UltrasonicSensor(5, 7);

int want_climb = 0;
int want_avoid = 0;

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

    if (accel_pitch > -15 && accel_pitch < 15)
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

    if (track_state == TrackSensor::ALL)   // TODO Encapsulate with inverted if-statement
    {
        new_state = MotorController::STOP;
    }

    want_climb = constrain(want_climb, 0, 15);
    motorControl.setState(new_state);
}

void hardAvoidObject()
{
    shield.setSpeed(60);
    shield.driveForward();

    steer_servo.write(110);
    delay(4000);
    steer_servo.write(70);
//    delay(4000);
//    steer_servo.write(90);
//    delay(800);
//    steer_servo.write(90);
//    delay(800);
}

void loop()
{
    dist_sensor.update();
    accel.update();
    steerSystem.update();
    updateMotorState();
    motorControl.update();

    if (dist_sensor.getDistance() < 100)
        want_avoid++;
    else
        want_avoid--;

    want_avoid = constrain(want_avoid, 0, 30);
    if( want_avoid > 20)
    {
        //hardAvoidObject();
        want_avoid = 0;
    }
    //Serial.print(" \tAngle: "); Serial.println(accel.getPitchAlt());
}
