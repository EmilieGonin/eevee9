#include "Items.h"

Items::Items(sf::Texture& texture, sqlite3* db) : AnimatedEntity(texture, db) {};
Items::~Items() {};

//bool getItem(Eevee* player) {
//	sf::Sprite sprite = player->getSprite(2, 2);
//	sf::FloatRect Eeveebounds = sprite.getGlobalBounds();
//	sf::Sprite items = item->getSprite();
//	sf::FloatRect Itembounds = item.getGlobalBounds();
//	if (Itembounds.intersects(Eeveebounds)) {
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}