#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, sqlite3* db) : AnimatedEntity(texture, db) {
	//
}
Enemy::~Enemy() {}


void Enemy::reset() {
	this->y = 0;
}

void Enemy::set() {
	std::cout << "Getting enemy datas..." << std::endl;
	std::vector<std::string> datas = getEnemy(this->db);

	this->name = datas[1];
	std::cout << stoi(datas[2]);
	this->hp = stoi(datas[2]);
	this->maxHp =stoi(datas[2]);
	this->speed = stoi(datas[3]);
	this->spriteFrames = stoi(datas[4]);

	//On relie la rangée de texture par rapport à l'id
	this->y = (stoi(datas[0]) - 1) * this->ySize;

	//Ajout des coordonnées + frames pour le combat
	this->setCoords(this->y, 96, 96, this->spriteFrames);
}