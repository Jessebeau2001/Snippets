#include "GameInstance.h"

GameInstance::GameInstance(int framerate) : framerate_(framerate), maxFrameInterval_((double) MILLISECONDS_IN_SECOND / framerate) { }

void GameInstance::start()
{
    while (true) {
        gameClock_.update();
        interval_ += gameClock_.deltaTime();
        if (interval_ > maxFrameInterval_) {
            interval_ -= maxFrameInterval_;
            update();
        }
    }
}

class Wave
{
    #include <string>

    private:
        int point = 1;
        int width = 16;
        int maxWidth = 64;
        bool right = true;

    public:
        void render()
        {
            if (right){
                point += 1;
            } else {
                point -= 1;
            }

            if(point < 2 || point > maxWidth - width - 2) right = !right;
            
            for (int i = 0; i < point; i++) std::cout << '#';
            for (int i = point; i < point + width; i++) std::cout << ' ';
            for (int i = point + width; i < maxWidth; i ++) std::cout << '#';

            std::cout << "\n";
        }
};

Wave wave;

void GameInstance::update()
{
    wave.render();
}
