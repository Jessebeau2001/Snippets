#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include "MotorController.h"

MotorController::MotorController(MotorShield * shield, PotMeter * speed_dial, Accelerometer * meter)
    : shield(shield), pot(speed_dial), meter(meter)
{
    ::init();
}

void MotorController::printDebug()
{
    Serial.println("Motor controller: ");
    Serial.println("> Motor shield: vvv");
    Serial.print("\t"); shield->printDebug();
    Serial.println("> Potmeter: vvv");
    Serial.print("\t"); pot->printDebug();
    Serial.print("Current target speed; ");
    Serial.println(current_speed);
}

void MotorController::init()
{
    // TODO maybe these should be optional parameters for an initializer list
    meter->setInterval(300);
}

void MotorController::update()
{
    float mod;

    switch (state)
    {
        case DRIVE:
            meter->update();    // TODO: This might cause problems
            mod = 1 + (meter->getPitch() / 20);
//            current_speed = pot->value(255) * mod;
            current_speed = default_speed * mod;    // Temp for disabled pot
            shield->driveForward();
            break;
        case SLOW:
            current_speed = turn_speed;
            shield->driveForward();
            break;
        case STOP:
            current_speed = 0;
            shield->brake();
            break;
    }

    shield->setSpeed(current_speed);
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
    return current_speed;
}

#pragma clang diagnostic pop
