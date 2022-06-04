#pragma once
#include "Vec2.hpp"
#include <SFML/Graphics/CircleShape.hpp>


/* Verlet integration */
/* x_n+1 = 2x_n - x_n-1 + a_n*dt*dt */
/* x_n+1 = x_n - v_n-1*dt + a_n*dt*dt */

struct VerletCircle
{
    Vec2 current_position;
    Vec2 prev_position;
    Vec2 acceleration;

    float radius;
    sf::CircleShape shape;

    VerletCircle()
    {
        current_position = {};
        prev_position = {};
        acceleration = {};

        radius = 100.0f;
        shape = sf::CircleShape(radius);
    }

    void update_position(float dt)
    {
        const Vec2 velocity = current_position - prev_position;
        prev_position = current_position;
        current_position = prev_position - velocity*dt + acceleration*dt*dt;

        shape.setPosition(current_position);
    }

    void accelerate(Vec2 acc)
    {
        acceleration += acc;
    }

};
