#pragma once
#include "Creature.hpp"

class Player;

class Monster : public Creature {
public:
	Monster() : Creature(200.0f, 30.0f, 15.0f) {}
	Monster(float hp, float mp, float attackDamage) : Creature(hp, mp, attackDamage) {}
protected:
	virtual void AttackPlayer(Player& player);
	virtual void Run();
};

class Slime : public Monster {
public:
	Slime() : Monster(50.0f, 10.0f, 5.0f) {}
	Slime(float hp, float mp, float attackDamage) : Monster(hp, mp, attackDamage) {}
};

class Gobline : public Monster {
public:
	Gobline() : Monster(100.0f, 0.0f, 5.0f) {}
	Gobline(float hp, float mp, float attackDamage) : Monster(hp, mp, attackDamage) {}
};

class Wildboar : public Monster {
public:
	Wildboar() : Monster(500.0f, 0.0f, 25.0f) {}
	Wildboar(float hp, float mp, float attackDamage) : Monster(hp, mp, attackDamage) {}
};