#include "vec2.hpp"
#include <iostream>
float x = 0.0f;
float y = 0.0f;

Vec2& Vec2::operator+=(Vec2 const& v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}
    
Vec2& Vec2::operator-=(Vec2 const& v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vec2& Vec2::operator*=(float s) {
    this->x *= s;
    this->y *= s;
    return *this;
}

Vec2& Vec2::operator/=(float s) {
    this->x /= s;
    this->y /= s;
    return *this;
}



