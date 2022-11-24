#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Entity
{
protected:

    int dodgerate;
    int hp;
    int orientation;
    sf::Sprite sprite;
    const sf::Texture& texture;

public:

    Entity(const sf::Texture& texture);

    sf::Sprite& getSprite(void);
    
    void setOrientation(int);
    int getOrientation();
    int getDodgerate();
};


