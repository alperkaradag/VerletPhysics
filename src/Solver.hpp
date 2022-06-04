#pragma once
#include "Vec2.hpp"
#include "VerletObject.hpp"
#include "ObjectManager.hpp"

#include <vector>

class Solver
{
private:
    Solver(){};

    void update_positions(float dt)
    {
        for(VerletCircle* obj : core::get_objects<VerletCircle>()){
            obj->update_position(dt);
        }
    }

    void apply_gravity()
    {
        for(VerletCircle* obj : core::get_objects<VerletCircle>()){
            obj->accelerate(gravity);
        }
    }

public:
    Solver(Solver const&) = delete;
    void operator=(Solver const&) = delete;

    static Solver& get_instance(){
        static Solver instance;
        return instance;
    }

    Vec2 gravity {0.0f, 1000.0f};

    void update(float dt)
    {
        apply_gravity();
        update_positions(dt);
    }
};
