#include "../../include/core/vec2d.h"

float fdse::Vec2D::length() const {
    return std::sqrt(x * x + y * y);
}
fdse::Vec2D fdse::Vec2D::normalized() const {
    float len = length();
    return (len != 0) ? fdse::Vec2D(x / len, y / len) : fdse::Vec2D(0, 0);
}
fdse::Vec2D fdse::Vec2D::operator+(const fdse::Vec2D& other) const{
    return fdse::Vec2D(x + other.x, y + other.y);
};
fdse::Vec2D fdse::Vec2D::operator-(const fdse::Vec2D& other) const {
    return fdse::Vec2D(x - other.x, y - other.y);
}
fdse::Vec2D fdse::Vec2D::operator*(float scalar) const {
    return fdse::Vec2D(x * scalar, y * scalar);
}
fdse::Vec2D& fdse::Vec2D::operator+=(const fdse::Vec2D& other) {
    x += other.x; y += other.y;
    return *this;
}
fdse::Vec2D& fdse::Vec2D::operator-=(const fdse::Vec2D& other) {
    x -= other.x; y -= other.y;
    return *this;
}