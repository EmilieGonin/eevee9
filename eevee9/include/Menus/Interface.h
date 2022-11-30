#pragma once

#include "Game.h"
#include "Eevee.h";

#include "Enemy.h"




class Interface
{
protected:
    int pos;
    int choice;
    bool pressed, startMenu, pauseMenu, battleMenu, display, state;

    float hpBarLength;
    int count;

    Game* _game;
    Eevee* eevee;

    Enemy* enemy;
    sf::RectangleShape* winclose;
    
    sf::Font* font;
    sf::Font* font2;
    sf::Texture* image;
    sf::Texture* lifebar;
    sf::Sprite* myHpBar;
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
    void drawComment(std::string, bool);

public:
    Interface(Game*, Eevee*, Enemy*);
    ~Interface();
    void start();
    void startOptions();
    void pause();
    void pauseOptions();
    int battle();
    void battleOptions();
    void beginningOptions();
    void stateOptions();

    void map();
    void displayComment(std::string, bool);

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
