#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include "Utils.h"

class Entity
{
protected:
    std::string name;
    int dodgerate;
    int speed;
    int hp;
    int orientation;
    sf::Sprite sprite;
    const sf::Texture& texture;

    //Sprite coordinates and sizes
    int spriteFrames;
    int y; //Determine which set of texture used
    int xSize;
    int ySize;

public:
    Entity(const sf::Texture& texture);

    //Setters
    void setHP(int);
    void subHP(int);
    void setOrientation(int);
    void setCoords(int, int, int, int);

    //Getters
    sf::Sprite getSprite();
    int getHP();
    int getOrientation();
    int getDodgerate();
    int getSpeed();
    std::string getName();
};


