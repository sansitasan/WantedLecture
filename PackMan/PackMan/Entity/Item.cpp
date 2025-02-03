#include "Item.h"
#include "Player.h"

Item::Item(const Vector2& position)
	: Super("S")
{
	this->position = position;
	entityColor = Color::BrightWhite;
}

Item::~Item()
{
}

bool Item::UseItem(Player& player)
{
	return true;
}
