#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Globals{

static double game_time = 0;
static double last_game_time = 0;
static double delta_time = 0;
static float fps;
static sf::Clock game_clock;

static float count_fps(const sf::RenderWindow& window){
    game_time = game_clock.getElapsedTime().asSeconds();
    delta_time = game_time - last_game_time;
    fps = 1.f / delta_time;
    last_game_time = game_time;
} 

}
