#pragma once
#include "Vec2.hpp"
#include "VerletObject.hpp"
#include "ObjectManager.hpp"

#include <vector>

class Solver
{
public:
    Solver(Solver const&) = delete;
    void operator=(Solver const&) = delete;

    static Solver& get_instance(){
        static Solver instance;
        return instance;
    }

    Vec2 gravity {0.0f, 500.0f};

    void update(float dt)
    {
        applyGravity();
        applyConstraint();
        updatePositions(dt);
    }


private:
    Solver(){};

    void updatePositions(float dt)
    {
        for(VerletCircle* obj : core::get_objects<VerletCircle>()){
            obj->updatePosition(dt);
        }
    }

    void applyGravity()
    {
        for(VerletCircle* obj : core::get_objects<VerletCircle>()){
            obj->accelerate(gravity);
        }
    }

    void applyConstraint()
    {
        const Vec2 pos{400.0f, 400.0f};
        const float radius = 300.0f;
        for(VerletCircle* obj : core::get_objects<VerletCircle>()){
            const Vec2 to_obj = obj->current_position - pos;
            const float dist = to_obj.length();

            if(dist > (radius - obj->radius)){
                const Vec2 dir = to_obj / dist;
                obj->current_position = pos + dir * (radius - obj->radius);
            }
        }
    }


};
