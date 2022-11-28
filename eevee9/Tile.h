#pragma once


class collision {
public:
	bool wall;
	bool tp;
	bool grass;
	bool item;

	void collideLeft();
	void collideRight();
	void collideUp();
	void collideDown();
};


