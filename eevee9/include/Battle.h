#pragma once

#include "Eevee.h"
#include "Enemy.h"
#include "Game.h"
#include "Interface.h"

class Battle
{
protected:
	bool _win, _loose, _caught, _escape, _positionSaved;
	int _choice; //1 = Attack, 2 = Escape
	int _choosen_attack; //Attaque de Eevee si choisie
	int _enemy_choice; //1 = Attack, 2 = Special Attack, 3 = Pokeball
	int _turn; //Number of turn
	Eevee* _eevee;
	Enemy* _enemy;
	Game* _game;
	Interface* interface;
	sf::Music music;
	sf::Music lowMusic;
	std::string musicTab[4] = { "./sfx/Music/battle.wav" , "./sfx/Music/battle2.wav" , "./sfx/Music/battle3.wav" , "./sfx/Music/battle4.wav" };
	std::string whatHappened;

public:
	Battle(Game*, Eevee*, Enemy*, Interface*);
	~Battle();
	//Reset battle datas
	void reset();
	//End battle loop
	void end();
	//Choose a random loot on a scale of 0 to 6, 0-3 = nothing
	void loot();
	//Check battle win & loose conditions
	bool battle();
	//Check player & enemy choices
	void turn();
	void attack(bool);
	bool pokeball();
	//If Eevee is faster than the enemy
	bool initiative();
	int random(int);
	int getDamage(bool);

	//Return: 0 = N'affecte pas, 0.5 = Pas efficace, 1 = Efficace, 2 = Très efficace
	double checkType(int, int, std::string);

	//Setters

	void setChoice(int);

	//Getters

	bool getChoice();
	bool getWin();
};

