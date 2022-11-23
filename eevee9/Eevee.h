#pragma once
#include "Entity.h"
#include <string>
#include <SFML/Graphics.hpp>


const int DOWN = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int UP = 3;

class Eevee : public Entity
{
protected:
	int catchrate;
	int orientation = DOWN;
	int count = 0;
	int iter = 0;
	sf::Sprite sprite;

	//Stones
	int firestone;
	int waterstone;
	int thunderstone;
public:
	Eevee(sf::Texture &);
	~Eevee();
	void evolve();
	bool canEvolve();
	void addLoot(int);
	bool escape();
	sf::Sprite getSprite();
	void update();
};



