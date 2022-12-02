#pragma once

#include "Eevee.h"

class Collision
{
protected:
	sf::RectangleShape& tile;

public:
	Collision(sf::RectangleShape &);
	sf::RectangleShape& gettile();
	bool getcollision(Eevee*);
};


