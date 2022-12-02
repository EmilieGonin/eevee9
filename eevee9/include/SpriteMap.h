#pragma once
#include "AnimatedEntity.h"
#include "Eevee.h"

class SpriteMap: public AnimatedEntity
{
public:
	SpriteMap(sf::Texture*);
	~SpriteMap();

	bool getItem(Eevee*);
};