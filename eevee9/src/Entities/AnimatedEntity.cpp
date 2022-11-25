#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(const sf::Texture& texture) : Entity(texture)
{
    this->count = 0;
    this->sprite.setTextureRect(sf::IntRect(0, 0, 132.5, 132.5));
}

void AnimatedEntity::update(void)
{
    spriteData eevee;
    if (this->count % 20 == 0)
    {
        this->frame = (this->frame + 1) % eevee.nbFrames;
        this->sprite.setTextureRect(sf::IntRect(this->frame * eevee.x, eevee.y * this->orientation, eevee.x_size, eevee.y_size));
        this->count = 0;
    }
    this->count++;
}
void AnimatedEntity::resetAnimation(void) {
    spriteData eevee;
    this->frame = 0;
    this->sprite.setTextureRect(sf::IntRect(this->frame * eevee.x, eevee.y * this->orientation, eevee.x_size, eevee.y_size));
    this->count = 0;
}