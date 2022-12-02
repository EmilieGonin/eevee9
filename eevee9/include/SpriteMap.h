#pragma once
#include "AnimatedEntity.h"
#include "Eevee.h"

class SpriteMap: public AnimatedEntity
{
protected:

	
public:
	SpriteMap(sf::Texture*);
	~SpriteMap();

	bool getItem(Eevee*);
};