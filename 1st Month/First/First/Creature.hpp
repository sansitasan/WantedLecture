#pragma once

class Creature {
public:
	Creature() : HP(100.0f), MP(50.0f), AttackDamage(10.0f) {}
	Creature(float hp, float mp, float attackDamage)
		: HP(hp), MP(mp), AttackDamage(attackDamage) {
	}
	inline virtual float GetHP();
	inline virtual void SetHP(float damage);
	inline virtual float GetMP();
	inline virtual bool SetMP(float useMPAmount);
protected:
	float HP;
	float MP;
	float AttackDamage;
};