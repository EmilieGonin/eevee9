#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include "Utils.h"
#include "Database.h"

class Entity
{
protected:
    std::string name;
    int dodgerate;
    int speed;
    int hp;
    int maxHp;
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
    void spritePosition(float x, float y);
    void setY(int);
    void setSpriteFrames(int);

    //Getters
    sf::Sprite getSprite(float, float);
    int getHP();
    int getMaxHP();
    int getOrientation();
    int getDodgerate();
    int getSpeed();
    std::string getName();
    int getY();
    int getSpriteFrames();
};


