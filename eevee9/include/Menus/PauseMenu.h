#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <SFML/Audio.hpp>


class PauseMenu {
    int pos;
    bool pressed, theselect;
    int timer;
  
    Game* game;
    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;
    sf::RenderWindow* window;
    sf::SoundBuffer buffer;
    sf::Sound button;
 
    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

protected:
    void set_values();
    
    void draw_all();

public:
    void loop_events();
    bool menu;
    PauseMenu(sf::RenderWindow*, Game* game);
    ~PauseMenu();
    void run_menu();
    bool getPlay();
};
