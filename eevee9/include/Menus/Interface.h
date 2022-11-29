#pragma once

#include "Game.h"
#include "Eevee.h";

class Interface
{
protected:
    int pos;
    bool pressed, theselect, startMenu, pauseMenu, battleMenu;

    Game* _game;
    Eevee* eevee;
    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Texture* image;
    sf::Sprite* bg;
    sf::RenderWindow* window;
    sf::Music music;
    sf::SoundBuffer buffer;
    sf::Sound button;
    sf::SoundBuffer bufferStart;
    sf::Sound startButton;

    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

    void loop_events();
    void draw_all();

public:
    Interface(Game*, Eevee*);
    ~Interface();
    void start();
    void startOptions();
    void pause();
    void pauseOptions();
    int battle();
    void battleOptions();
    void map();

    //Setters
    void stopMusic();
    void setPauseMenu(bool);
    void setTexts(int);

    //Getters
    int getPos();
    bool getStartMenu();
    bool getPauseMenu();
    bool getBattleMenu();
};
