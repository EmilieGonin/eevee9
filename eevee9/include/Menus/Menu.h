#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>


class Menu{
    int pos;
    bool pressed, theselect;
    

    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;
    sf::RenderWindow* window;
    sf::Music music;
    sf::SoundBuffer buffer;
    sf::Sound button;

    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

protected:
    void set_values();
    void loop_events();
    void draw_all();

public:
    bool menu;
    Menu(sf::RenderWindow*);
    ~Menu();
    void run_menu();
    bool getPlay();
};
