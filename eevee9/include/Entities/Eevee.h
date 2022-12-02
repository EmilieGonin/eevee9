#pragma once

#include "AnimatedEntity.h"

class Eevee : public AnimatedEntity
{
protected:
	sf::Vector2f mapPosition;
	int map;

	//Evolution
	int eeveelution; //0 = not evolved, 1 = Vaporeon, 2 = Jolteon, 3 = Flareon
	bool evolved;
  
	//Inventory
	int waterstone, thunderstone, firestone, money, step;

public:
	Eevee(sf::Texture&, sqlite3*);
	~Eevee();
	void evolve(int);
	bool canEvolve();
	void addLoot(int, int);
	void move(bool);
	void collisionNotMoving(bool);
	int catchrate();

	//Setters

	void set(int);
	void setMapPosition(sf::Vector2f);

	//Getters

	int getMap();
	int getEeveelution();
	bool isEvolved();
	int getFire();
	int getWater();
	int getThunder();
	int getMoney();
	int getStep();
	sf::Vector2f getMapPosition();
};



