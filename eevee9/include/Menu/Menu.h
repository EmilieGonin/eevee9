#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Menu{
    int pos;
    bool pressed, theselect;
    bool menu;

    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;
    sf::RenderWindow* window;
   
    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

protected:
    void set_values();
    void loop_events();
    void draw_all();

public:
    Menu(sf::RenderWindow*);
    ~Menu();
    void run_menu();
    bool getPlay();
};
