#include "Player.hpp"
#include "Monster.hpp"

void Player::AttackMonster(Monster& monster)
{
	monster.SetHP(AttackDamage);
}
