#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include "Time.h"
#include <iostream>

class GameComponent
{
    public:
        virtual void update() = 0;
};

class GameInstance
{
    private:
        const int MILLISECONDS_IN_SECOND = 1000;
        const int framerate_;
        const double maxFrameInterval_;

        double interval_{};
        Time gameClock_{};

    public:
        GameInstance(int framerate = 60);
        void start();
        void update();
};

#endif