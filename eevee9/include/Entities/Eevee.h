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

	//Evolution
	int eeveelution; // 1 = Vaporeon, 2 = Jolteon, 3 = Flareon
	bool evolved;
  
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

	//Getters
	int getEeveelution();
	bool isEvolved();
};



