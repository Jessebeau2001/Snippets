/******************************************************************************

Vector 2 struct example in c++
This could use some work, seperate implementation and prototype into header
and source files. Also implement vector math function like rotate, normal, etc

*******************************************************************************/

#include <iostream>

struct Vec2
{
    float x, y;
    
    Vec2(float x = 0, float y = 0) : x(x), y(y) {}
    Vec2(const Vec2 & other) : x(other.x), y(other.y) {}
    
    void Set(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    
    void PrintData()
    {
        std::cout << *this << std::endl;
    }
    
    Vec2 & operator= (const Vec2 & other);
    Vec2 & operator+ (const Vec2 & other);
    Vec2 & operator- (const Vec2 & other);
    Vec2 & operator* (const float & scalar);
    friend std::ostream & operator<< (std::ostream & os, const Vec2 & vec);
};

Vec2 & Vec2::operator+ (const Vec2 & other)
{
    x += other.x;
    y += other.y;
}

Vec2 & Vec2::operator- (const Vec2 & other)
{
    x -= other.x;
    y -= other.y;
}

Vec2 & Vec2::operator* (const float & scalar)
{
    x *= scalar;
    y *= scalar;
}

Vec2 & Vec2::operator= (const Vec2 & other)
{
    x = other.x;
    y = other.y;
}

std::ostream & operator<< (std::ostream & os, const Vec2 & vec)
{
    os << "(X: " << vec.x << ", Y: " << vec.y << ")";
    return os;
}

class Player
{
    private:
        Vec2 pos_;
    
    public:
        Player(float x = 0, float y = 0) : pos_(x, y) {}
        Player(Vec2 pos) : pos_(pos) {}
        
        void SetPos(float x, float y)
        {
            pos_.Set(x, y);
        }
};


int main()
{
    Vec2 test{};
    return 0;
}
