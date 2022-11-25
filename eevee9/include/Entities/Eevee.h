#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "AnimatedEntity.h"

class Eevee : public AnimatedEntity
{
protected:
	int catchrate;
	int count = 0;
	int iter = 0;
  
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
	void move();
};



