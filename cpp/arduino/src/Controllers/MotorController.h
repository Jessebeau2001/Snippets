#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Components/MotorShield.h"
#include "Components/PotMeter.h"
#include "Components/Accelerometer.h"
#include "Interfaces/SimpleInterfaces.h"


class MotorController : IUpdatable, IInitializable, IPrintable
{
public: enum motorState { DRIVE, SLOW, STOP };
private:
    MotorShield * shield;
    PotMeter * pot;
    Accelerometer * meter;

    uint8_t default_speed = 80;
    uint8_t turn_speed = 50;

    motorState state = STOP;
    uint8_t current_speed{};

public:
    MotorController(MotorShield * shield, PotMeter * speed_dial, Accelerometer * meter); // Const pointer, not pointer to const obj

    void init() override;
    void update() override;
    void printDebug() override;
    void setState(const motorState & new_state);

    const motorState & getState() const;
    const uint8_t & getTargetSpeed() const;
};

#endif
