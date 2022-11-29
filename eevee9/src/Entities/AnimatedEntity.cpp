#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(const sf::Texture& texture) : Entity(texture)
{
    this->count = 0;
    this->frame = 0;
}

void AnimatedEntity::update(void)
{
    if (this->count % 5 == 0)
    {
        this->frame = (this->frame + 1) % this->spriteFrames;
        this->sprite.setTextureRect(sf::IntRect(this->frame * this->xSize, this->y + this->ySize * this->orientation, this->xSize, this->ySize));
        this->count = 0;
    }
    this->count++;
}
void AnimatedEntity::resetAnimation(void) {
    this->frame = 0;
    this->sprite.setTextureRect(sf::IntRect(this->frame * this->xSize, this->y + this->ySize * this->orientation, this->xSize, this->ySize));
    this->count = 0;
}

void AnimatedEntity::idle(void) {
    //std::cout << "idle" << std::endl;
    if (this->count % 200 == 0)
    {
        this->frame = (this->frame + 1) % this->spriteFrames;
        this->sprite.setTextureRect(sf::IntRect(this->frame * this->xSize, this->y, this->xSize, this->ySize));
        this->count = 0;
    }
    this->count++;
}