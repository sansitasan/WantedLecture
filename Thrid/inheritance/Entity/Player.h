#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(const char* name);
	~Player();

private:
	char* name;
};

