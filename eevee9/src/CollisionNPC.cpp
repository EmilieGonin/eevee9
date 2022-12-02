#include "CollisionNPC.h"

CollisionNPC::CollisionNPC(sf::Sprite& sprite) : sprite(sprite) {};

bool CollisionNPC::getcollision(Eevee* player) {
	sf::FloatRect NPCbounds = this->sprite.getGlobalBounds();
	sf::Sprite sprite = player->getSprite(2, 2);
	sf::FloatRect Eeveebounds = sprite.getGlobalBounds();

	if (NPCbounds.intersects(Eeveebounds)) {
		return 1;
	}
	else {
		return 0;
	}
}