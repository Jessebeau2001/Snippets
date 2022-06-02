#ifndef IDELAYABLE_H
#define IDELAYABLE_H

#include <Arduino.h>

class IDelayable {
private:
    unsigned long last_time = millis();
public:
    void setInterval(const short & new_interval) { this->interval = new_interval; }

    const short & getInterval() const { return interval; }

protected:
    short interval = 1000;
    short elapsed = 0;

    bool wait()
    {
        elapsed += calc_elapsed();
        if (elapsed < interval)
            return true;

        elapsed -= interval;
        return false;
    }

    short calc_elapsed()
    {
        unsigned long time = millis();
        auto c_elapsed = (int) (millis() - last_time);
        last_time = time;
        return c_elapsed;
    }
};

#endif
