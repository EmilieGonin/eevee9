#pragma once
#include "Eevee.h"
#include <SFML/Graphics.hpp>



class Collision {
public:
	bool wall;
	bool tp;
	bool grass;
	bool item;
	float x;
	float y;
	sf::RectangleShape &tile;
	sf::RectangleShape &gettile();

	Collision(sf::RectangleShape &, bool, bool);


	bool getcollision(Eevee*);
};


