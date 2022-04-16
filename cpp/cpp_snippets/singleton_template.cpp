/******************************************************************************

Singleton template example,
example is done with a simple Player class that has a 2D position

*******************************************************************************/

#include <iostream>

template <typename T>
class Singleton
{
    protected:
        Singleton(const T & obj) : obj_{obj} {}
        static Singleton * singleton_;
        T obj_;
    
    public:
        Singleton(Singleton & other) = delete;          // Not cloneable
        void operator= (const Singleton &) = delete;    // Not assignable
        static Singleton * GetInstance(const T & obj);
        T & GetObject() { return obj_; }
};

template <typename T>
Singleton<T> * Singleton<T>::singleton_ = nullptr;

template <typename T>
Singleton<T> * Singleton<T>::GetInstance(const T & obj)
{
    if (singleton_ == nullptr) {
        singleton_ = new Singleton(obj);
    }
    return singleton_;
}

class Player
{
    private:
        float x_, y_;
    
    public:
        Player() : x_{0}, y_{0} {}
        Player(float x, float y) : x_{x}, y_{y} {}
        
        void PrintData()
        {
            std::cout << "Player pos: (X: " << x_ << ", Y: " << y_ << ")\n";
        }
        
        void SetPos(float x, float y)
        {
            x_ = x;
            y_ = y;
        }
};

void DoStuff()
{
    Player & player =  Singleton<Player>::GetInstance(Player{})->GetObject();
    player.SetPos(120, 155);
}

int main()
{
    Player & player =  Singleton<Player>::GetInstance(Player{})->GetObject();
    player.PrintData();
    DoStuff();
    player.PrintData();
    
    return 0;
}
