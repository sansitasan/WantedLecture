#include "GameScene.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Entity/Player.h"
#include "Entity/DrawableEntity.h"
#include "Entity/Wall.h"
#include "Entity/Box.h"
#include "Entity/Target.h"
#include "Entity/Ground.h"
#include "Entity/SPlayer.h"
#include <Windows.h>

GameScene::GameScene()
{
	Engine::Get().SetCursorType(ECursorType::NoCursor);
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Maps/Stage1.txt", "rb");

	if (!file) { 
		std::cout << "맵 파일 열기 실패.\n";
		__debugbreak();
		return; 
	}

	//포인터 끝으로
	fseek(file, 0, SEEK_END);

	size_t readSize = ftell(file);

	//포인터 차렷 원위치
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	char* buffer = new char[readSize + 1];
	memset(buffer, 0, readSize);
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead) {
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
	}

	buffer[readSize] = '\0';

	int index = 0;
	int xPos = 0, yPos = 0;

	while (index < (int)bytesRead) {
		char mapChar = buffer[index++];
		if (mapChar == '\n') {
			++yPos;
			xPos = 0;
			continue;
		}

		if (mapChar == '1') {
			Wall* wall = new Wall(Vector2((float)xPos, (float)yPos));
			SceneEntityList.PushBack(wall);
			map.PushBack(wall);
		}

		else if (mapChar == 't') {
			Target* target = new Target(Vector2((float)xPos, (float)yPos));
			SceneEntityList.PushBack(target);
			targets.PushBack(target);
		}

		else if (mapChar != ' ') {
			Ground* ground = new Ground(Vector2((float)xPos, (float)yPos));
			SceneEntityList.PushBack(ground);
			map.PushBack(ground);

			if (mapChar == 'b') {
				Box* box = new Box(Vector2((float)xPos, (float)yPos));
				SceneEntityList.PushBack(box);
				boxes.PushBack(box);
			}

			else if (mapChar == 'p') {
				player = new SPlayer(Vector2((float)xPos, (float)yPos), this);
				SceneEntityList.PushBack(player);
			}
		}

		++xPos;
	}

	delete[] buffer;

	fclose(file);
}

GameScene::~GameScene()
{
}

void GameScene::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE)) {
		Engine::Get().QuitEngine();
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::Green);
	Engine::Get().SetCursorPosition(0, (int)Engine::Get().GetScreenSize().GetY() + 3);
	Log("MoveCount: %d", moveCount);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::White);
}

void GameScene::Draw()
{
	for (DrawableEntity* entity : map) {
		if (entity->GetPosition() == player->GetPosition()) continue;

		entity->Draw();
	}

	for (Target* target : targets) {
		target->Draw();
	}

	for (Box* box : boxes) {
		box->Draw();
	}

	player->Draw();
}

bool GameScene::CanPlayerMove(const Vector2& position)
{
	DrawableEntity* searchedEntity = nullptr;
	for (DrawableEntity* entity : map) {
		if (entity->GetPosition() == position) {
			searchedEntity = entity;
			break;
		}
	}

	if (searchedEntity->As<Wall>()) return false;
	return true;
}
