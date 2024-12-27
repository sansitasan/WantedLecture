#include "Entity.h"
#include <iostream>

Entity::Entity()
	:x(0), y(0) 
{
	std::cout << "Entity() called\n";
}

Entity::Entity(int x, int y)
	:x(x), y(y) {}

Entity::~Entity()
{
	std::cout << "~Entity() called\n";
}

void Entity::Move(int xAmount, int yAmount)
{
	x += xAmount;
	y += yAmount;
}
