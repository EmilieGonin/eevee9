#pragma once

#include "Game.h"
#include "Eevee.h";
#include "Enemy.h"
#include "Items.h"

class Interface
{
protected:
    int pos, choice, count, mapId;
    bool pressed, startMenu, pauseMenu, battleMenu, display, evolveMenu;
    int hpBarLength, ennemyHpBarLength;

    Game* _game;
    Eevee* eevee;
    Enemy* enemy;

    sf::RectangleShape* winclose;
    sf::Font* font;
    sf::Font* font2;
    sf::Texture* image;
    sf::Sprite* bg;
    sf::RenderWindow* window;
    sf::Music music;
    sf::SoundBuffer buffer;
    sf::Sound button;
    sf::SoundBuffer bufferStart;
    sf::Sound startButton;
    std::string mapLinks[3] = { "./img/map.png", "./img/map2.png", "./img/map3.png" };

    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

    void loop_events();
    void draw_all();
    void drawEevee();
    void drawComment(std::string, bool);

public:
    Interface(Game*, Eevee*, Enemy*);
    ~Interface();

    //Classic menus

    void start();
    void startOptions();
    void pause();
    void pauseOptions();

    //Battle menus

    int battle();
    void battleOptions();
    void evolve();
    void evolveOptions();
    void beginningOptions();
    void displayComment(std::string, bool);
    void displayInfo(std::string);

    //Map

    void map();
    void changeMap(bool);

    //Setters

    void stopMusic();
    void setPauseMenu(bool);
    void setTexts(int);
    void setMap(int);

    //Getters

    int getPos();
    bool getStartMenu();
    bool getPauseMenu();
    bool getBattleMenu();
    bool getMapId();
};
