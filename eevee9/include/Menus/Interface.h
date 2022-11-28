#pragma once

#include "Game.h"

class Interface
{
protected:
    int pos;
    bool pressed, theselect, startMenu, pauseMenu, battleMenu;

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
    void battle(bool);
    void battleOptions();
    void map();

    //Setters
    void setPauseMenu(bool);
    void setTexts(int);

    //Getters
    int getPos();
    bool getStartMenu();
    bool getPauseMenu();
    bool getBattleMenu();
};
