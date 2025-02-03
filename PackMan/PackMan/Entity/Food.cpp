#include "Food.h"

Food::Food(const Vector2& position)
	: Super(".")
{
	this->position = position;
	entityColor = Color::White;
}

Food::~Food()
{
}
