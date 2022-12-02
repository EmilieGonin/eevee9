#include "Eevee.h"

Eevee::Eevee(sf::Texture &texture, sqlite3* db) : AnimatedEntity(texture, db) {
	//Sprite
	this->xSize = 30;
	this->ySize = 28;

	//Evolution
	this->eeveelution = 0;
	this->evolved = false;

	this->set(0);
};

Eevee::~Eevee() {};

void Eevee::set(int id) {
	std::cout << "setting eevee's datas..." << std::endl;
	//Fetch player datas
	//1[Name(100)], 2[HP int], 3[Attack int], 4[Speed int]
	//5[Frames int], 6[Type int], 7[x], 8[y]
	std::vector<std::string> playerDatas = getPlayer(this->db, id);

	if (!id) {
		this->evolved = false;
		this->eeveelution = 0;
	}
	else {
		this->eeveelution = id;
		this->spritePosition(std::stof(playerDatas[7]), std::stof(playerDatas[8]));
	}

	//Stats
	this->name = playerDatas[1]; // le joueur peut modifier ?
	this->maxHp = stoi(playerDatas[2]);
	this->attack = stoi(playerDatas[3]);
	this->speed = stoi(playerDatas[4]);
	this->type = stoi(playerDatas[6]);

	//Sprite
	this->spriteFrames = stoi(playerDatas[5]);

	//Fetch save datas
	//1[HP int], 2[Waterstone], 3[Thunderstone], 4[Firestone], 5[Map],
	//6[x], 7[y], 8[Orientation], 9[Money], 10[Step]
	std::vector<std::string> datas = getSave(this->db);

	if (!this->evolved) {
		this->hp = stoi(datas[1]);
	}
	else {
		this->hp = stoi(playerDatas[2]);
	}

	//Inventory
	this->waterstone = stoi(datas[2]);
	this->thunderstone = stoi(datas[3]);
	this->firestone = stoi(datas[4]);
	this->money = stoi(datas[9]);
	this->step = stoi(datas[10]);

	//Position
	this->map = stoi(datas[5]);
	this->orientation = stoi(datas[8]);
	this->mapPosition.x = stoi(datas[6]);
	this->mapPosition.y = stoi(datas[7]);
	std::cout << "done !" << std::endl;
}

void Eevee::evolve(int eeveelution) {
	this->eeveelution = eeveelution - 2;
	std::cout << "Eeveelution choosen : " << this->eeveelution << std::endl;
	this->evolved = true;
	this->set(this->eeveelution);
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
	this->step++;

	if (this->step == 1000) {
		std::cout << "After walking so much, you found a shard !" << std::endl;
		this->addLoot(random(3) + 1, 0);
		this->step = 0;
	}

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
bool Eevee::isEvolved() { return this->evolved; }
int Eevee::getMoney() { return this->money; }
int Eevee::getStep() { return this->step; }
sf::Vector2f Eevee::getMapPosition() { return this->mapPosition;  }
