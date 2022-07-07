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
        const int substeps = 4;
        const float sub_dt = dt / substeps;
        for(int i = substeps; i--;){
            applyGravity();
            applyConstraint();
            solveCollisions();
            updatePositions(sub_dt);
        }
    }


private:
    Solver(){};

    void updatePositions(float dt)
    {
        for(VerletCircle* obj : core::get_objects_set<VerletCircle>()){
            obj->updatePosition(dt);
        }
    }

    void applyGravity()
    {
        for(VerletCircle* obj : core::get_objects_set<VerletCircle>()){
            obj->accelerate(gravity);
        }
    }

    void applyConstraint()
    {
        const Vec2 pos{800.0f, 450.0f};
        const float radius = 400.0f;
        for(VerletCircle* obj : core::get_objects_set<VerletCircle>()){
            const Vec2 to_obj = obj->current_position - pos;
            const float dist = to_obj.length();

            if(dist > (radius - obj->radius)){
                const Vec2 dir = to_obj / dist;
                obj->current_position = pos + dir * (radius - obj->radius);
            }
        }
    }

    void solveCollisions()
    {
        auto objs = core::get_objects_vector<VerletCircle>();
        for(int i = 0; i < objs.size(); i++){
            VerletCircle* obj1 = objs[i];
            for(int j = i+1; j < objs.size(); j++){
                VerletCircle* obj2 = objs[j];
                const Vec2 collision_axis = obj1->current_position - obj2->current_position;
                const float distance = collision_axis.length();
                if(distance < obj1->radius + obj2->radius){
                    const Vec2 direction = collision_axis / distance;
                    const float delta = obj1->radius + obj2->radius - distance;
                    obj1->current_position += 0.5f * delta * direction;
                    obj2->current_position -= 0.5f * delta * direction;
                }
            }
        }
    }
};
