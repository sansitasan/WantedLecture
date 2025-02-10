#include "Monster.hpp"
#include "Player.hpp"
#include <iostream>

void Monster::AttackPlayer(Player& player)
{
	player.SetHP(AttackDamage);
}

void Monster::Run()
{
	std::cout << "¸ó½ºÅÍ´Â µµ¸Á°¬´Ù!" << '\n';
}
