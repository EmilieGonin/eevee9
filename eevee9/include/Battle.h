#pragma once

#include "Eevee.h"
#include "Enemy.h"

class Battle
{
protected:
	bool _fighting;
	bool _win;
	bool _loose;
	int _choice; //1 = Attack, 2 = Escape
	int _choosen_attack; //Attaque de Eevee si choisie
	int _enemy_choice; //1 = Attack, 2 = Special Attack, 3 = Pokeball
	int _turn; //Number of turn
	Eevee* _eevee;
	Enemy* _enemy;

public:
	Battle(Eevee*, Enemy*);
	~Battle();
	void loot(); // Choose a random loot on a scale of 0 to 6, 0-3 = nothing
	void battle();
	void turn();
	void attack(bool);
	bool pokeball();
	bool initiative();
	int random(int);
};

