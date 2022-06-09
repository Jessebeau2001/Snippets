#include "vec2.h"
#include "math.h"

vec2 vec2::forward = vec2(0, 1);

void vec2::print() const
{
    Serial.print("X: "); Serial.print(x);
    Serial.print(", Y: "); Serial.println(y);
}

float vec2::length() const
{
    return sqrt(x * x + y * y);
}

float vec2::dot(const vec2 & other) const
{
    return this->x * other.x + this->y * other.y;
}

float vec2::angle(const vec2 & other) const
{
    return acos(this->dot(other)) * (180 / M_PI);
}

bool vec2::isZero() const {
    return x == 0 && y == 0;
}

void vec2::normalize()
{
    auto l = length();
    if (l <= 0) return;
    x /= l;
    y /= l;
}

void vec2::zero() {
    x = 0;
    y = 0;
}

vec2 vec2::operator+ (const vec2 & other) const
{
    return {this->x + other.x, this->y + other.y};
}

vec2 & vec2::operator+= (const vec2 & other)
{
    this->x += other.x;
    this->y += other.y;
    return * this;
}
