#pragma once

#include <math.h>
#include <SFML/System/Vector2.hpp>
#include <string>
#include "Globals.hpp"

struct Vec2
{
    float x;
    float y;

    inline float length() const {
        return (float)sqrtl(x*x + y*y);
    }
    
    operator sf::Vector2f() const {
        return sf::Vector2f(x, y);
    } 

    std::string toString(){
        return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }

    static Vec2 random_vector(int x_min, int x_max, int y_min, int y_max){
        float x = Globals::rand_int(x_min, x_max);
        float y = Globals::rand_int(y_min, y_max);
        return Vec2{x, y};
    }
};

/**************** OPERATORS ****************/
Vec2 operator+(const Vec2& lhs, const Vec2& rhs){
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vec2& operator+=(Vec2& lhs, const Vec2& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs){
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

Vec2& operator-=(Vec2& lhs, const Vec2& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

Vec2 operator*(const Vec2& lhs, float s) {
    return {lhs.x * s, lhs.y * s};
}
Vec2 operator*(float s, const Vec2& rhs) {
    return rhs * s;
}
Vec2& operator*=(Vec2& lhs, float s) {
    lhs.x *= s;
    lhs.y *= s;
    return lhs;
}

Vec2 operator/(const Vec2& lhs, float s) {
    return {lhs.x / s, lhs.y / s};
}
Vec2& operator/=(Vec2& lhs, float s) {
    lhs.x /= s;
    lhs.y /= s;
    return lhs;
}