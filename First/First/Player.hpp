#pragma once
#include "Creature.hpp"

class Monster;

class Player : public Creature {
public:
	Player() : Creature(150.0f, 100.0f, 20.0f), Gold(0.0f) {}
protected:
	virtual void AttackMonster(Monster& monster);
	float Gold;
};