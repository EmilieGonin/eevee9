#pragma once
#include "Entity.h"
#include <string>

class Eevee : public Entity
{
protected:
	int catchrate;

	//Coordonates
	//int x;
	//int y;
public:
	Eevee();
	~Eevee();
	void evolve();
	bool canEvolve();
	void addStone(std::string);
	bool escape();
};

