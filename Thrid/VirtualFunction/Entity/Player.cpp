#include "Player.h"
#include <iostream>

Player::Player(const char* name)
{
	size_t len = strlen(name) + 1;

	this->name = new char[len];
	strcpy_s(this->name, len, name);
}

Player::~Player()
{
	if (name) {
		delete[] name;
	}
}