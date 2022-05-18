#include <Arduino.h>
#include "../.pio/libdeps/uno/Servo/src/Servo.h"
#include "TrackSensor.h"
#include "MotorDriver.h"
#include "MotorController.h"

byte sensor_pins[5] = { A0, A2, A3, A4, A5 };
TrackSensor tracker = TrackSensor(5, sensor_pins);

//Servo steer;
MotorController control = MotorController(4, 7, 6, A1, 100, true);

//int angle = 0;
//float mod = 1.4;

void setup()
{
    Serial.begin(9600);
    while (!Serial) { }
    tracker.printDebug();
    control.printDebug();

//    steer.attach(9);
}

void loop()
{
//    tracker.printSegments();
//    motor2.driveForward();
//    steer.write(90 + (angle * mod));
}
