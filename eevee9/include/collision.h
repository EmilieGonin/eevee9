#pragma once

#include "Eevee.h"
#include <SFML/Graphics.hpp>

class Collision
{
public:
	float x;
	float y;
	sf::RectangleShape &tile;
	sf::RectangleShape &gettile();

	Collision(sf::RectangleShape &);
	bool getcollision(Eevee*);
};


