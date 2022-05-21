#include <Arduino.h>
#include "Controllers/SteerSystem.h"
#include "Controllers/MotorController.h"

//byte tracker_pins[5] = { 2, 3, 11, 12, 13 };
//TrackSensor_Digital tracker = TrackSensor_Digital(5, tracker_pins);
//Servo steer_servo;
//SteerSystem steerSystem = SteerSystem(&tracker, &steer_servo, 10);

MotorShield shield = MotorShield(4, 9, 6, A1, 55, true); // Motor B
PotMeter pot = PotMeter(A3);
Accelerometer accel = Accelerometer(0x68);
MotorController motorControl = MotorController(&shield, &pot, &accel);


void setup()
{
    Serial.begin(9600);

    accel.init();
    motorControl.init();
    motorControl.setState(MotorController::DRIVE);
}

void loop()
{
    Serial.print("Target speed: "); Serial.print(motorControl.getTargetSpeed()); Serial.println();
//    Serial.print(", "); pot.printDebug();
    motorControl.update();
}

