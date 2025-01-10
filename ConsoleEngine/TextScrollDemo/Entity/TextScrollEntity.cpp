#include "TextScrollEntity.h"
#include "Engine/Engine.h"

TextScrollEntity::TextScrollEntity(const char* message)
{
	length = (int)strlen(message);

	str = new char[length + 1];
	strcpy_s(str, length + 1, message);
	Engine::Get().SetCursorType(ECursorType::NoCursor);
}

TextScrollEntity::~TextScrollEntity()
{
	delete[] str;
}

void TextScrollEntity::Update(float deltaTime)
{
	index = (index + 1) % length;
}

void TextScrollEntity::Draw()
{
	char* temp = new char[printWidth + 1];
	int tempIndex = index;

	for (int i = 0; i < printWidth; ++i) {
		temp[i] = str[tempIndex];
		tempIndex = (tempIndex + 1) % length;
	}

	temp[printWidth] = '\0';
	Log(temp);
	delete[] temp;
	//Engine::Get().SetCursorPosition(0, 0);
}
