#ifndef SIMPLEINTERFACES_H
#define SIMPLEINTERFACES_H

#include "IDelayable.h"

class IPrintable                // For everything that is printable
{
    virtual void printDebug() = 0;
};

class IInitializable            // For all components
{
    virtual void init() = 0;
};

class IUpdatable                // For all sensors (they need an update call before data can be read)
{
    virtual void update() = 0;
};

#endif
