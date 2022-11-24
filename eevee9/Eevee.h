#pragma once
#include "Entity.h"
#include "Utils.h"
#include <string>
#include <SFML/Graphics.hpp>




class Eevee : public Entity
{
protected:
	int catchrate;
	int orientation = DOWN;
	int count = 0;
	int iter = 0;
	sf::Sprite sprite;
  
	//Coordonates
	int changeX = 0.f;
	int changeY = 0.f;
  
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
	void setOrientation(int orientation);
	int getOrientation();
	void move();
};



