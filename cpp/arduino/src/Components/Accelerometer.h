#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "Interfaces/ISensor.h"
#include "Interfaces/IDelayable.h"
#include <Wire.h>
#include <vec2.h>

// TODO: try make this extension of vec2
struct vec3 : IPrintable
{
    int x{}, y{}, z{};

    vec3() = default;

    vec3(int x, int y, int z) : x(x), y(y), z(z) { }

    void printDebug() override
    {
        Serial.print("(X: "); Serial.print(x);
        Serial.print(", Y: "); Serial.print(y);
        Serial.print(", Z: "); Serial.print(z);
        Serial.print(")");
    }

    vec3 & operator+= (const vec3 & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return * this;
    }
};

class Accelerometer : ISensor, public IDelayable
{
private:
    static const vec3 pos_offset; // NOLINT(bugprone-dynamic-static-initializers)
    static const vec3 gyro_offset;// NOLINT(bugprone-dynamic-static-initializers)

    const int address;

    vec3 pos{};
    vec3 gyro{};    // No Quaternions :((

    double pitch{};
    double roll{};

public:
    explicit Accelerometer(const int & address) : ISensor(0), address(address)
    {

    }

    void init() override
    {
        Wire.begin();
        Wire.beginTransmission(address);
        Wire.write(0x6B);
        Wire.write(0);
        Wire.endTransmission(true);
    }

    void update() override
    {
        if (wait())
            return;

        Wire.beginTransmission(address);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(address, 14, true);

        pos.x = readWire();
        pos.y = readWire();
        pos.z = readWire();
        pos += pos_offset;

//        readWire();             // Normally it would give the temp here, but we dump that;
//        gyro.x = readWire();    // ALL DISABLED CUZ ITS UNUSED
//        gyro.y = readWire();    // Or maybe stop car with to radical reading cuz that might tell us the car crashed
//        gyro.z = readWire();
//        gyro += gyro_offset;

        calcAngles();
    }

    const double & getPitch() const
    {
        return pitch;
    }

    void printDebug() override
    {
        Serial.print("Pitch/roll: "); Serial.print(pitch); Serial.print(", "); Serial.print(roll);
        Serial.print(", inertia: "); pos.printDebug();
        Serial.print(", axis inertia: "); gyro.printDebug();
        Serial.println();
    }

protected:
    void calcAngles()
    {
        pitch = (double) atan( pos.x / sqrt( pow(pos.y, 2) + pow(pos.z, 2))) * (180 / M_PI);
        roll = (double) atan( pos.y / sqrt( pow(pos.x, 2) + pow(pos.z, 2))) * (180 / M_PI);
    }

    static int readWire()
    {
        return Wire.read() << 8 | Wire.read();
    }
};

#endif
