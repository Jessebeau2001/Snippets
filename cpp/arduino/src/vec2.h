#ifndef VEC2_H
#define VEC2_H

#include <Arduino.h>

struct vec2
{
    float x, y;

    vec2(float x, float y) : x(x), y(y) { }
    vec2() : x(0), y(0) { }

    static vec2 forward;

    float length() const;
    float dot(const vec2 & other) const;
    float angle(const vec2 & other) const;

    void normalize();
    void zero();

    vec2 operator+ (const vec2 & other) const;
    vec2 & operator+=(const vec2 & other);

    void print() const;
};

#endif
