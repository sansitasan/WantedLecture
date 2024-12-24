#include "Creature.hpp"

float Creature::GetHP() {
	return HP;
}

void Creature::SetHP(float damage) {
	HP -= HP - damage > 0 ? damage : HP;
}

float Creature::GetMP() {
	return MP;
}

bool Creature::SetMP(float useMPAmount) {
	if (useMPAmount > MP) return false;
	MP -= useMPAmount;
	return true;
}