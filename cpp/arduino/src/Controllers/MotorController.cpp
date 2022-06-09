#include "MotorController.h"

MotorController::MotorController(MotorShield * shield, Accelerometer * meter)
    : shield(shield), meter(meter) // TODO: Rename meter
{
    ::init();
}

void MotorController::printDebug()
{
    Serial.println("Motor controller: ");
    Serial.println("> Motor shield: vvv");
    Serial.print("\t"); shield->printDebug();
    Serial.print("Current target speed; ");
    Serial.println(target_speed);
}

void MotorController::init()
{ }

void MotorController::update()
{
    switch (state)
    {
        case DRIVE:
            target_speed = drive_speed;
//            Serial.print("Driving with speed: "); Serial.print(target_speed);
            shield->driveForward();
            break;
        case TURN:
            target_speed = turn_speed;
//            Serial.print("Turning with speed: "); Serial.print(target_speed);
            shield->driveForward();
            break;
        case CLIMB:
            target_speed = climb_speed * (1 + (meter->getPitchAlt() / 40));
//            Serial.print("Climbing with speed: "); Serial.print(target_speed);
            target_speed = drive_speed; // This line disables climb state
            shield->driveForward();
            break;
        case STOP:
            target_speed = 60;
            shield->reverse();
            delay(200);     // Todo: maybe decrease
            target_speed = 0;
//            Serial.print("Car is stopped: "); Serial.print(target_speed);
            shield->brake();
            break;
    }

    shield->setSpeed(target_speed);
}

void MotorController::setState(const motorState & new_state)
{
    state = new_state;
}

const MotorController::motorState & MotorController::getState() const
{
    return state;
}

const uint8_t &MotorController::getTargetSpeed() const
{
    return target_speed;
}

int8_t MotorController::calcClimbSpeed(const int8_t & speed_in, const int8_t & pitch) {
    return speed_in * (1 + (pitch / 40)); // TODO somehow this doesnt work
}
