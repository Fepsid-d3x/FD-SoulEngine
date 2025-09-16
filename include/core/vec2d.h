#ifndef VEC2D_H
#define VEC2D_H

#include <cmath>

namespace fdse{
    struct Vec2D {
        float x, y;

        Vec2D() : x(0), y(0) {}
        Vec2D(float x_, float y_) : x(x_), y(y_) {}

        Vec2D operator+(const Vec2D& other) const;
        Vec2D operator-(const Vec2D& other) const;
        Vec2D operator*(float scalar) const;
        Vec2D& operator+=(const Vec2D& other);
        Vec2D& operator-=(const Vec2D& other);

        float length() const;
        Vec2D normalized() const;
    };
}

#endif