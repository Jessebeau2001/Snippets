#ifndef SIMPLEINTERFACES_H
#define SIMPLEINTERFACES_H

#include "../.pio/libdeps/uno/LiquidCrystal_I2C/LiquidCrystal_I2C.h"

// TODO: Change printing function on all classes to this ESPECIALLY ICOMPONENT AND CHILDREN
class IPrintable
{
public:
    virtual void printDebug() = 0;
};

class ILCDPrintable
{
    virtual void LCDPrint(LiquidCrystal_I2C * lcd) = 0;
};

class IInitializable
{
    virtual void init() = 0;
};

class IDelayable
{
    int8_t interval{};
    int8_t clock{};

    virtual void updateDelay() = 0;
};

#endif
