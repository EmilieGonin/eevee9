#include "Battle.h"

Battle::Battle(Game* game, Eevee* eevee, Enemy* enemy, Interface* interface) {
	this->_eevee = eevee;
	this->_enemy = enemy;
	this->_game = game;
	this->interface = interface;
	
	/*this->music.openFromFile("./sfx/Music/strongBattle.wav");*/
	this->music.setLoop(true);
	this->music.setVolume(10);

	this->lowMusic.setLoop(true);
	this->lowMusic.setVolume(10);

	this->reset();
}

Battle::~Battle() {};

void Battle::reset() {
	this->_win = this->_loose = this->_escape = false;
	this->_choice = this->_choosen_attack = this->_enemy_choice = 0;
	this->_turn = 1;
	this->_enemy->set();
	this->_positionSaved = false;
}

void Battle::end() {
	std::cout << "BATTLE ENDED" << std::endl;
	std::cout << "----------" << std::endl << std::endl;
	if (this->_win) {
		
		this->lowMusic.stop();

		if(this->music.getVolume() == 0)
		{
			int goalVolume = 20;
			int volume = 0;
			while(volume != goalVolume)
			{
				volume++;
				this->music.setVolume(volume);
			}
		}
		this->interface->displayComment(this->_enemy->getName() + " fainted...", this->_win - 1);
		this->music.stop();
		this->interface->displayComment("You win", this->_win);
		this->loot();
	}
	else if (this->_loose) {
		std::cout << "You loose..." << std::endl;
		this->_eevee->setHP(this->_eevee->getMaxHP());
		this->_enemy->setHP(this->_enemy->getMaxHP());
		this->interface->setMap(1); //reset eevee and puts it at his spawn
	}

	if (this->music.getStatus() == 2) {
		this->music.stop();
		this->lowMusic.stop();
	}

	this->_eevee->spritePosition(this->_eevee->getMapPosition().x, this->_eevee->getMapPosition().y);
	this->_eevee->setCoords(0, 30, 28, 3);
	this->_enemy->reset();
	this->reset();
}

void Battle::loot() {
	int loot = this->random(6);
	std::cout << "Getting loot : " << loot << std::endl;

	if (loot > 3) {
		this->_eevee->addLoot(loot - 3);
	}
}

bool Battle::battle() {
	//Music
	float percent = 20.0 / 100.0;

	if (this->music.getStatus() != 2) {
		if (this->_eevee->getHP() < percent * this->_eevee->getMaxHP()) {
			std::cout << "je suis low";
			this->music.setVolume(0);

			if (this->lowMusic.getStatus() != 2) {
				this->lowMusic.openFromFile("./sfx/Music/lowHp.wav");
				this->lowMusic.play();
			}
		}
		else {
			this->music.setVolume(20);
		}

		this->music.openFromFile(musicTab[this->random(4)]);
		this->music.play();
	}

	if (!this->_positionSaved) {
		std::cout << "Eevee map position saved !" << std::endl;
		this->_eevee->setMapPosition(this->_eevee->getSprite(2, 2).getPosition());
		this->_positionSaved = true;
	}

	//std::cout << "You encountered a wild " << this->_enemy->getName() << " !" << std::endl;
	
	//On vérifie les conditions de win
	this->_win = this->_enemy->getHP() <= 0;
	this->_loose = this->_eevee->getHP() <= 0;
	this->_game->setBattle(!this->_win && !this->_loose && !this->_escape);

	if (!this->_game->getBattle()) {
		this->end();
		return 0;
	}
	else {
		return 1;
	}
}

void Battle::turn() {
	std::cout << "BATTLE TURN : " << this->_turn << std::endl;
	std::cout << "[Turn fonction] Choice : " << this->_choice << std::endl;
	//La fuite passe toujours en premier
	if (this->_choice == 2) {
		bool escape = this->random(2);

		if (escape) {
			this->interface->displayComment("You got away safely..", this->_win);
			this->_choice = 0;
			this->_enemy_choice = 0;
			this->_escape = true;
			return;
		}
		else {
			
			this->interface->displayComment("You couldn't get away !", this->_win);
		}
	}

	//Sélection de l'ennemi
	std::cout << "Calculating ennemy's choice..." << std::endl;

	//Au premier tour, on ne pourra pas se faire attraper
	if (this->_turn == 1) {
		this->_enemy_choice = this->random(2) + 1;
	}
	else {
		this->_enemy_choice = this->random(3) + 1;
	}

	//Debug only
	std::cout << "----------" << std::endl;
	std::cout << "Enemy choose " << this->_enemy_choice << std::endl;
	std::cout << "----------" << std::endl;

	//L'ennemi lancera toujours sa Pokeball avant notre attaque
	if (this->_enemy_choice == 3) {

		this->interface->displayComment("Enemy trow a pokeball !", this->_win);
		if (this->pokeball()) {
			this->interface->displayComment("You've been caught...", this->_win);
			this->_loose = true;
			
		}
		else {
			this->interface->displayComment("You escaped the pokeball !", this->_win);
		}
	}

	//S'il reste une action d'attaque à effectuer, on lance l'attaque
	if (this->_enemy_choice != 3 && this->_choice != 2) {
		//Si les deux doivent attaquer, on calcule l'initiative
		std::cout << "Calculating eevee's speed..." << std::endl;
		bool eevee = this->initiative();
		this->attack(eevee);
		if (this->battle()) {
			this->attack(!eevee);
		}
	}
	else if (this->_enemy_choice != 3 || this->_choice == 1) {
		if (this->_choice == 1) {
			this->attack(true);
		}
		else {
			this->attack(false);
		}
	}

	this->_choice = 0;
	this->_enemy_choice = 0;
	this->_turn++;
}

//
void Battle::attack(bool eevee) {
	//std::cout << "Attack function" << std::endl;
	int dodgerate;
	std::string name;

	if (!this->_eevee->isEvolved() && this->_eevee->getEeveelution()) {
		std::cout << "Eevee evolve !" << std::endl;
		//Evolve
	}

	//On vérifie si c'est l'attaque de Eevee
	if (eevee) {
		//Si c'est le cas, on récupère la dodgerate de l'ennemi
		this->interface->displayComment("You attack !", this->_win);
		dodgerate = this->_enemy->getDodgerate();
	}
	else {
		//Sinon, celle d'Eevee
		this->interface->displayComment(this->_enemy->getName() + " attacks!", this->_win);
		dodgerate = this->_eevee->getDodgerate();
	}
		
	if (this->random(100) > dodgerate) {
	
		//Attack succeed
		//if special attack, bonus to dmg + different animation
		if (eevee) {
			//Si c'est Eevee qui attaque, on baisse les HP de l'ennemi
			this->_enemy->subHP(10); //temp dmg
			this->interface->displayComment("You attack !", this->_win);
		}
		else {
			//Sinon, c'est Eevee qui perds de la vie
			this->_eevee->subHP(10);
			this->interface->displayComment(this->_enemy->getName() + " attacks!", this->_win);
			std::cout << this->_eevee->getHP();
			float percent = 20.0 / 100.0;

			if (this->_eevee->getHP() < percent * this->_eevee->getMaxHP()) {
				std::cout << "je suis low";
				this->music.setVolume(0);
				if (this->lowMusic.getStatus() != 2) {
					this->lowMusic.openFromFile("./sfx/Music/lowHp.wav");
					this->lowMusic.play();
				}
			}
		}
	}
	else {
		if (eevee) { //Si c'est Eevee qui attaque, c'est l'ennmi qui a dodge
			this->interface->displayComment(this->_enemy->getName() + " has dodged the attack !", this->_win);
		}
		else {
			this->interface->displayComment("You dodged the attack !", this->_win);
		}
	}
}

bool Battle::pokeball() {
	if (this->random(200) <= this->_eevee->catchrate()) {
		return true;
	}
	else {
		return false;
	}
}

bool Battle::initiative() {
	return this->_eevee->getSpeed() > this->_enemy->getSpeed();
}

int Battle::random(int range ) {
	srand(time(0));
	int random = rand() % range;
	return random;
}

//Setters

void Battle::setChoice(int choice) {
	std::cout << "i choose";
	this->_choice = choice;
}

//Getters

bool Battle::getChoice() { return this->_choice; }
bool Battle::getWin() { return this->_win; }

