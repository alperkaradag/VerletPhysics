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

    VerletCircle* vo = core::New<VerletCircle>();
    vo->shape.setFillColor(sf::Color::Green);

    //sf::CircleShape shape(100.f);

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
        }

        window.clear();
        Solver::get_instance().update(Globals::delta_time);
        for(auto s : core::get_objects<VerletCircle>()){
            window.draw(s->shape);
        }
        window.display();
    }

    return 0;
}