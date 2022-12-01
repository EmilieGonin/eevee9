#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, sqlite3* db) : AnimatedEntity(texture, db) {
	//
}
Enemy::~Enemy() {}


void Enemy::reset() {
	this->y = 0;
}

void Enemy::set() {
	//1[Name(100)], 2[HP int], 3[Attack int], 4[Speed int], 5[Frames int], 6[Type int], 7[Rarities int]
	std::cout << "Getting enemy datas..." << std::endl;
	std::vector<std::string> datas = getEnemy(this->db);

	this->name = datas[1];
	this->hp = this->maxHp = stoi(datas[2]);
	this->attack = stoi(datas[3]);
	this->speed = stoi(datas[4]);
	this->spriteFrames = stoi(datas[5]);
	this->type = stoi(datas[6]);

	//On relie la rangée de texture par rapport à l'id
	this->y = (stoi(datas[0]) - 1) * this->ySize;

	//Ajout des coordonnées + frames pour le combat
	this->setCoords(this->y, 96, 96, this->spriteFrames);
}