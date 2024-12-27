#include "Player.h"
#include <iostream>

Player::Player(const char* name)
	: Entity()
{
	std::cout << "Player() called\n";
	size_t len = strlen(name) + 1;

	this->name = new char[len];
	strcpy_s(this->name, len, name);
}

Player::~Player()
{
	std::cout << "~Player() called\n";
	if (name) {
		delete[] name;
	}
}