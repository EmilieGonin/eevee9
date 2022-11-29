#pragma once
#include "Eevee.h"
#include <SFML/Graphics.hpp>

class Test {
public:
	bool wall;
	bool tp;
	bool grass;
	bool item;
	float x;
	float y;
	sf::RectangleShape* tile;

	Test(float, float, bool);

	void collideLeft();
	void collideRight();
	void collideUp();
	void collideDown();

	bool collision(Eevee*);
};


