#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>

struct Vec2
{
    float x;
    float y;

    Vec2 operator+(const Vec2& v) const {
        return {x + v.x, y + v.y};
    }
    Vec2& operator+=(const Vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    
    Vec2 operator-(const Vec2& v) const {
        return {x - v.x, y - v.y};
    }
    Vec2& operator-=(const Vec2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    Vec2 operator*(float s) const {
        return {x * s, y * s};
    }
    Vec2& operator*=(float s) {
        x *= s;
        y *= s;
        return *this;
    }
    

    operator sf::Vector2f() const {
        return sf::Vector2f(x, y);
    } 

    std::string toString(){
        return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
};