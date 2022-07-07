#include <SFML/Graphics.hpp>

#include <iostream>

#include "Globals.hpp"
#include "VerletObject.hpp"
#include "ObjectManager.hpp"
#include "Solver.hpp"

using namespace std;

int main()
{
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(1600, 900), "main");
    window.setFramerateLimit(60.0f);

    /*VerletCircle* vo = core::New<VerletCircle>(Vec2{400.0f, 200.0f}, 30.0f);
    vo->shape.setFillColor(sf::Color::Green);*/

    sf::CircleShape constraintShape(400.f, 1<<7);
    constraintShape.setFillColor(sf::Color(142, 142, 142));
    constraintShape.setOrigin(sf::Vector2f(400.0f, 400.0f));
    constraintShape.setPosition(sf::Vector2f(800.0f, 450.0f));

    while (window.isOpen())
    {
        Globals::count_fps(window);
        string title = "fps: " + to_string((int)Globals::fps) + " obj: " + to_string(core::get_object_count<VerletCircle>());
        window.setTitle(title);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){
                Vec2 mousePos{(float)event.mouseButton.x, (float)event.mouseButton.y};
                if(event.mouseButton.button == sf::Mouse::Left){
                    core::New<VerletCircle>(mousePos, 10.0f);
                }
                else if(event.mouseButton.button == sf::Mouse::Right){
                    for(int i = 0; i < 100; i++){
                        Vec2 rvec = Vec2::random_vector(-30, 30, -30, 30);
                        core::New<VerletCircle>(mousePos + rvec, Globals::rand_int(5, 10));
                    }
                }
            }
        }

        window.clear();
        Solver::get_instance().update(Globals::delta_time);
        window.draw(constraintShape);
        for(auto s : core::get_objects_set<VerletCircle>()){
            window.draw(s->shape);
        }
        window.display();
    }

    return 0;
}