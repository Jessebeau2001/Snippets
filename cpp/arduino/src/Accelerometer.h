#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "ISensor.h"
#include <Wire.h>

struct vec3 : IPrintable
{
    int8_t x{}, y{}, z{};

    vec3() = default;

    vec3(int8_t x, int8_t y, int8_t z) : x(x), y(y), z(z) { }

    void printDebug() override
    {
        Serial.print("Vec3: (X: "); Serial.write(x);
        Serial.print(", Y: "); Serial.write(y);
        Serial.print(", Z: "); Serial.write(z);
    }
};

struct coord : IPrintable
{
    int8_t x{}, y{}, z{};
    int8_t gX{}, gY{}, gZ{};

    coord() = default;

    void printDebug() override
    {
        Serial.print("Coord: (X: "); Serial.write(x);
        Serial.print(", Y: "); Serial.write(y);
        Serial.print(", Z: "); Serial.write(z);

        Serial.print(", gX"); Serial.write(gX);
        Serial.print(", gY: "); Serial.write(gY);
        Serial.print(", gZ: "); Serial.write(gZ);
        Serial.println(")");
    }

    coord(int8_t x, int8_t y, int8_t z, int8_t Gx, int8_t Gy, int8_t Gz)
            : x(x), y(y), z(z), gX(Gx), gY(Gy), gZ(Gz) { }
};

class Accelerometer : ISensor
{
private:
    int address;
    coord data{};

public:
    explicit Accelerometer(const int & address) : ISensor(0), address(address)
    {
        ::init();
    }

    coord * getData()
    {
        update();
        return &data;
    }

protected:
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
        Wire.beginTransmission(address);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(address, 12, true);

        data.x = readWire();
        data.y = readWire();
        data.z = readWire();
        data.gX = readWire();
        data.gY = readWire();
        data.gZ = readWire();
    }

    static int8_t readWire()
    {
        return (int8_t) (Wire.read() << 8 | Wire.read());
    }
};

#endif
