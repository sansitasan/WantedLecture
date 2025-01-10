#pragma once
#include "Entity/Entity.h"

class TextScrollEntity : public Entity
{
	RTTI_DECLARATIONS(TextScrollEntity, Entity)

public:
	TextScrollEntity(const char* message);
	~TextScrollEntity();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	char* str = nullptr;
	int index = 0;
	int length = 0;

	int printWidth = 20;
};

