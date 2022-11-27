#pragma once

#include <SFML/Graphics.hpp>
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
    //sf::Sprite& getSprite(void);
    sf::Sprite getSprite();
    void setOrientation(int);
    int getOrientation();
    int getDodgerate();
    int getSpeed();
    std::string getName();
};


