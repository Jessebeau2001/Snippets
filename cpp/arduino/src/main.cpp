#include <Arduino.h>
#include "TrackSensor.h"

byte sensor_pins[] = {A0, A1, A2, A3, A4 };
TrackSensor sens = TrackSensor(5, sensor_pins);;

void setup()
{
    Serial.begin(9600);
    while (!Serial) {}
    sens.printDebug();
}

void loop()
{
    sens.publicUpdateCallForDebug();
    //sens.printSegments();
}
