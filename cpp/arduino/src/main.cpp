//#include "../.pio/libdeps/uno/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include <Arduino.h>
#include "MotorShield.h"
#include "SteerSystem.h"
#include "ButtonSwitch.h"

#include "Accelerometer.h"

#include <Wire.h>

byte tracker_pins[5] = { 2, 3, 11, 12, 13 };
TrackSensor_Digital tracker = TrackSensor_Digital(5, tracker_pins);
Servo steer_servo;
SteerSystem steerSystem = SteerSystem(&tracker, &steer_servo, 10);

MotorShield motor = MotorShield(4, 9, 6, A1, 55, true); // Motor B

//Accelerometer gyro = Accelerometer(0x68);

void setup()
{
    Serial.begin(9600);

    steerSystem.init();
}

void loop()
{
    steerSystem.update();
    motor.driveForward();

//    if (tracker.getState() != TrackSensor::LOST)
//        motor.driveForward();
//    else
//        motor.brake();
}

