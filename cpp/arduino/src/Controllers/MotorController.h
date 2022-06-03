#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Components/MotorShield.h"
#include "Components/PotMeter.h"
#include "Components/Accelerometer.h"
#include "Interfaces/SimpleInterfaces.h"


class MotorController : IUpdatable, IInitializable, IPrintable
{
public: enum motorState { DRIVE, TURN, CLIMB, STOP }; // TODO: Maybe descent
private:
    MotorShield * shield;
    Accelerometer * meter;

    uint8_t drive_speed = 50;
    uint8_t turn_speed = 55;
    uint8_t climb_speed = 120;

    motorState state = STOP;    // Default start state should be ALL
//    uint8_t current_speed{};
    uint8_t target_speed{};

public:
    MotorController(MotorShield * shield, Accelerometer * meter); // Const pointer, not pointer to const obj

    void init() override;
    void update() override;
    void printDebug() override;
    void setState(const motorState & new_state);

    const motorState & getState() const;
    const uint8_t & getTargetSpeed() const;

    static int8_t calcClimbSpeed(const int8_t & speed_in, const int8_t & pitch);
};

#endif
