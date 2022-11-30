#pragma once

#include "Entity.h"

class AnimatedEntity : public Entity
{
protected:
    int count;
    int frame;

public:
    AnimatedEntity(const sf::Texture&, sqlite3*);
    void update(void);
    void resetAnimation(void);
    void idle(void);
};