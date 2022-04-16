#include "Time.h"
#include <ctime>

Time::Time()
{
    time_ = clock();
    lastTime_ = time_;
}

void Time::update()
{
    time_ = clock();
    deltaTime_ = (double) (time_ - lastTime_);
    lastTime_ = time_;
}

double const & Time::deltaTime() const { return deltaTime_; }