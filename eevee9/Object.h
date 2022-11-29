#pragma once
#include "Eevee.h"

class Object {
public:
	bool wall;
	bool tp;
	bool grass;
	bool item;

	void collideLeft();
	void collideRight();
	void collideUp();
	void collideDown();

	void collision(Eevee*);
};


