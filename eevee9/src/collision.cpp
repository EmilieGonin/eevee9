#include "Collision.h"

Collision::Collision(sf::RectangleShape& rectangle) : tile(rectangle) {};
sf::RectangleShape& Collision::gettile() { return this->tile; };

bool Collision::getcollision(Eevee* player) {
	sf::FloatRect bounds = this->tile.getGlobalBounds();
	sf::Sprite sprite = player->getSprite(2, 2);
	sf::FloatRect Eeveebounds = sprite.getGlobalBounds();
	
	if (bounds.intersects(Eeveebounds)) {
		return 1;
	}
	else {
		return 0;
	}
}