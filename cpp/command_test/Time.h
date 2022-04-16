#ifndef TIME_H
#define TIME_H

#include <ctime>

class Time
{
    private:
        clock_t time_;
        clock_t lastTime_;
        double deltaTime_;

    public:
        Time();
        void update();
        double const & deltaTime() const;
};

#endif