#pragma once
#include "Entity.h"

class AnimatedEntity : public Entity
{
protected:

        int count = 0;
        int frame = 0;

public:
    AnimatedEntity(const sf::Texture&);
    void update(void);
};