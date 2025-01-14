#include "TextScrollEntity.h"
#include "Engine/Engine.h"

TextScrollEntity::TextScrollEntity(const char* message)
{
	length = (int)strlen(message);

	str = new char[length + 1];
	strcpy_s(str, length + 1, message);
	Engine::Get().SetCursorType(ECursorType::NoCursor);
	KEYBIND(MoveRight, TextScrollEntity, VK_RIGHT, KEYDOWN);
	KEYBIND(MoveLeft, TextScrollEntity, VK_LEFT, KEYDOWN);
}

TextScrollEntity::~TextScrollEntity()
{
	KEYUNBIND(MoveRight, TextScrollEntity, VK_RIGHT, KEYDOWN);
	KEYUNBIND(MoveLeft, TextScrollEntity, VK_LEFT, KEYDOWN);
	delete[] str;
}

void TextScrollEntity::Update(float deltaTime)
{
	if (!shouldUpdate) return;

	elapsedTime += deltaTime;

	if (elapsedTime < delayTime) {
		return;
	}

	elapsedTime = 0;


	switch (direction)
	{
	case TextScrollEntity::Direction::Left:
		index = (index + 1) % length;
		break;
	case TextScrollEntity::Direction::Right:
		index = (index - 1) % length;
		break;
	default:
		break;
	}
}

void TextScrollEntity::Draw()
{
	char temp[printWidth + 1];
	int tempIndex = index;

	for (int i = 0; i < printWidth; ++i) {
		temp[i] = str[tempIndex];
		tempIndex = (tempIndex + 1) % length;
	}

	temp[printWidth] = '\0';
	Log(temp);
}

void TextScrollEntity::MoveLeft()
{
	direction = Direction::Left;
}

void TextScrollEntity::MoveRight()
{
	direction = Direction::Right;
}
