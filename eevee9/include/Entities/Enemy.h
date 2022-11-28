#pragma once

#include "AnimatedEntity.h"

class Enemy : public AnimatedEntity
{
protected:
	sf::Sprite sprite;

public:
	Enemy(sf::Texture&);
	~Enemy();
};