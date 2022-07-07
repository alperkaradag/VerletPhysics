#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <ctime>

namespace Globals{

double game_time = 0;
double last_game_time = 0;
double delta_time = 0;
float fps;
sf::Clock game_clock;

float count_fps(const sf::RenderWindow& window){
    game_time = game_clock.getElapsedTime().asSeconds();
    delta_time = game_time - last_game_time;
    fps = 1.f / delta_time;
    last_game_time = game_time;
    return fps;
} 

uint8_t rand_byte(){
    return (uint8_t)rand();
}

uint32_t rand_color(){
    uint32_t r = (uint32_t)rand_byte() << 24;
    uint32_t g = (uint32_t)rand_byte() << 16;
    uint32_t b = (uint32_t)rand_byte() << 8;
    uint32_t a = 0x000000FF;
    return r | g | b | a;
}

int rand_int(int min_limit, int max_limit){
    return rand() % (max_limit - min_limit) + min_limit;
}

}
