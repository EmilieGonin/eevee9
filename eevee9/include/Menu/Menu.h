#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>


class Menu : public Game 
{
    int pos;
    bool pressed, theselect, play;

    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;

   
    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

protected:
    void set_values();
    void loop_events();
    void draw_all();

public:
    Menu();
    ~Menu();
    void run_menu();
    bool getPlay();
};
