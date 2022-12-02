#include "SpriteMap.h"

SpriteMap::SpriteMap(sf::Texture* texture) : AnimatedEntity(*texture, db) {};
SpriteMap::~SpriteMap() {};

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