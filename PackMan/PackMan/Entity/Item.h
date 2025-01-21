
#pragma once
#include <Entity/DrawableEntity.h>

class Item : public DrawableEntity {
	RTTI_DECLARATIONS(Item, DrawableEntity)
public:
	Item(const Vector2& position);
	virtual ~Item();
	bool UseItem(class Player& player);
private:

};