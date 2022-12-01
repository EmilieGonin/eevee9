#pragma once

#include "AnimatedEntity.h"

class Eevee : public AnimatedEntity
{
protected:
	sf::Vector2f mapPosition;
	int iter = 0;

	//Evolution
	int eeveelution; //0 = not evolved, 1 = Vaporeon, 2 = Jolteon, 3 = Flareon
	bool evolved;
  
	//Stones
	int firestone;
	int waterstone;
	int thunderstone;

public:
	Eevee(sf::Texture&, sqlite3*);
	~Eevee();
	void evolve(int);
	bool canEvolve();
	void addLoot(int);
	bool escape();
	void move(bool);
	void collisionNotMoving(bool);
	int catchrate();

	//Setters
	void setMapPosition(sf::Vector2f);

	//Getters
	int getEeveelution();
	bool isEvolved();
	sf::Vector2f getMapPosition();
};



