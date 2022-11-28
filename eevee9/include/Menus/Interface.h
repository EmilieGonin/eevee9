#pragma once

#include "Game.h"

class Interface
{
protected:
    int pos;
    bool pressed, theselect, startMenu, pauseMenu;

    Game* _game;
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

    void loop_events();
    void draw_all();

public:
    Interface(Game*);
    ~Interface();
    void start();
    void startOptions();
    void pause();
    void pauseOptions();

    //Setters
    void setPauseMenu(bool);
    void setTexts();

    //Getters
    bool getStartMenu();
    bool getPauseMenu();
};
