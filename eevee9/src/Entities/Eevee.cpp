#include "Eevee.h"

Eevee::Eevee(sf::Texture &texture, sqlite3* db) : AnimatedEntity(texture, db) {
	//Sprite
	this->xSize = 30;
	this->ySize = 28;

	//Evolution
	this->eeveelution = 0;
	this->evolved = false;

	this->set();
};

Eevee::~Eevee() {};

void Eevee::set() {
	std::cout << "setting eevee's datas..." << std::endl;
	//Fetch player datas
	//1[Name(100)], 2[HP int], 3[Attack int], 4[Speed int]
	//5[Frames int], 6[Type int]
	std::vector<std::string> datas = getPlayer(this->db);

	//Stats
	this->name = datas[1]; // le joueur peut modifier ?
	this->maxHp = stoi(datas[2]);
	this->attack = stoi(datas[3]);
	this->speed = stoi(datas[4]);
	this->type = stoi(datas[6]);

	//Sprite
	this->spriteFrames = stoi(datas[5]);

	//Fetch save datas
	//1[HP int], 2[Waterstone], 3[Thunderstone], 4[Firestone], 5[Map],
	//6[x], 7[y], 8[Orientation]
	datas = getSave(this->db);

	this->hp = stoi(datas[1]);

	//Stones
	this->waterstone = stoi(datas[2]);
	this->thunderstone = stoi(datas[3]);
	this->firestone = stoi(datas[4]);

	//Position
	this->map = stoi(datas[5]);
	this->orientation = stoi(datas[8]);
	this->mapPosition.x = stoi(datas[6]);
	this->mapPosition.y = stoi(datas[7]);
	std::cout << "done !" << std::endl;
}

void Eevee::evolve(int eeveelution) {
	this->eeveelution = eeveelution+1;

	int frame = 0;

	if (eeveelution == 1) { //Vaporeon
		frame = 54;
	}
	else if (eeveelution == 2) { //Jolteon
		frame = 50;
	}
	else if (eeveelution == 3) { //Flareon
		frame = 84;
	}

	this->spriteFrames = frame;
}

bool Eevee::canEvolve() {
	if (this->firestone > 0 || this->waterstone > 0 || this->thunderstone > 0) {
		return true;
	}
	else {
		return false;
	}
}

int Eevee::getFire() { return this->firestone; }
int Eevee::getWater(){ return this->waterstone; }
int Eevee::getThunder(){ return this->thunderstone; }

void Eevee::addLoot(int loot, int money) {
	if (loot == 1) {
		this->firestone++;
	}
	else if (loot == 2) {
		this->waterstone++;
	}
	else if (loot == 3) {
		this->thunderstone++;
	}

	this->money += money;
}

void Eevee::collisionNotMoving(bool collision) {
	if(collision)
	{
		if (this->orientation == UP)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + 5);
		}
		else if (this->orientation == DOWN)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 5);
		}
		else if (this->orientation == RIGHT)
		{
			this->sprite.setPosition(this->sprite.getPosition().x - 5, this->sprite.getPosition().y);
		}
		else if (this->orientation == LEFT)
		{
			this->sprite.setPosition(this->sprite.getPosition().x + 5, this->sprite.getPosition().y);
		}
	}
}
void Eevee::move(bool collision) {
	int changeX = 0;
	int changeY = 0;

	if (this->orientation == DOWN) {
		changeY = 2; 
	}
	if (this->orientation == UP) {
		 changeY = -2; 
	}
		
	if (this->orientation == RIGHT) {
		 changeX = 2; 
		}
	if (this->orientation == LEFT) {
		 changeX = -2; 
		}

	if (!collision) {
		this->sprite.move(changeX * PAS, changeY * PAS);
	}
	else {
		if (this->orientation == UP)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + 1);
		}
		else if (this->orientation == DOWN)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 1);
		}
		else if (this->orientation == RIGHT)
		{
			this->sprite.setPosition(this->sprite.getPosition().x - 1, this->sprite.getPosition().y);
		}
		else if (this->orientation == LEFT)
		{
			this->sprite.setPosition(this->sprite.getPosition().x + 1, this->sprite.getPosition().y);
		}
	}	
}

int Eevee::catchrate() {
	int HpLeft = (100 * this->hp) / this->maxHp;
	int catchrate = (100 - HpLeft) / 2 + 6;
	std::cout << HpLeft << "% HP left. Catchrate : " << catchrate << std::endl;
	return catchrate;
}

//Setters

void Eevee::setMapPosition(sf::Vector2f position){
	this->mapPosition = position;
}

//Getters	

int Eevee::getMap() { return this->map; }
int Eevee::getEeveelution() { return this->eeveelution; }
int Eevee::getMoney() {
	return this->money;
}
bool Eevee::isEvolved() { return this->evolved; }
sf::Vector2f Eevee::getMapPosition() { return this->mapPosition;  }
