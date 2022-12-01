#pragma once
#include "AnimatedEntity.h"
#include "Eevee.h"

class Items : public AnimatedEntity
{
protected:
	sf::Sprite item;

public:
	Items(sf::Texture&, sqlite3*);
	~Items();

	bool getItem(Eevee*);
};