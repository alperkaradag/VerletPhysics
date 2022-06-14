#include <SFML/Graphics.hpp>

#include <iostream>

#include "Globals.hpp"
#include "VerletObject.hpp"
#include "ObjectManager.hpp"
#include "Solver.hpp"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "main");
    window.setFramerateLimit(60.0f);

    /*VerletCircle* vo = core::New<VerletCircle>(Vec2{400.0f, 200.0f}, 30.0f);
    vo->shape.setFillColor(sf::Color::Green);*/

    sf::CircleShape constraintShape(300.f, 1<<7);
    constraintShape.setFillColor(sf::Color(142, 142, 142));
    constraintShape.setOrigin(sf::Vector2f(300.0f, 300.0f));
    constraintShape.setPosition(sf::Vector2f(400.0f, 400.0f));

    while (window.isOpen())
    {
        Globals::count_fps(window);
        string title = "fps: " + to_string((int)Globals::fps);
        window.setTitle(title);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    Vec2 mousePos{(float)event.mouseButton.x, (float)event.mouseButton.y};
                    core::New<VerletCircle>(mousePos, 30.0f, sf::Color::Cyan);
                }
            }
        }

        window.clear();
        Solver::get_instance().update(Globals::delta_time);
        window.draw(constraintShape);
        for(auto s : core::get_objects<VerletCircle>()){
            window.draw(s->shape);
        }
        window.display();
    }

    return 0;
}