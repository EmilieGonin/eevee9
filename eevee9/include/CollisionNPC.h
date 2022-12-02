#pragma once

#include "Eevee.h"
#include "SpriteMap.h"
#include <SFML/Graphics.hpp>

class CollisionNPC
{
public:
	float x;
	float y;
	sf::Sprite & sprite;
	CollisionNPC(sf::Sprite &);
	bool getcollision(Eevee*);
};


