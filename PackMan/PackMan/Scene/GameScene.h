#pragma once
#include <Scene/Scene.h>
#include <Math/Vector/Vector2.h>

class DataManager;

class GameScene : public Scene
{
	RTTI_DECLARATIONS(GameScene, Scene)
private:
	enum class EEntitys {
		None,
		Wall,
		Food,
		Item,
		Player,
		Enemy
	};
public:
	GameScene(const DataManager& dataManager);
	virtual ~GameScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	bool CanMove(Vector2& position, Entity* entity = nullptr);

	void ChangeX(Vector2& position);

private:
	bool IsGameClear();
	void EndGame();
	void CollisionEnemyAndPlayer();
private:
	int moveCount = 0;
	bool isClear = false;
	std::string map;
	int width;
	int height;
	int score;
	int foodAndItemCounts = 0;
	DrawableEntity** entityMap;
	class Player* player;
	std::vector<class Enemy*> enemies;
	std::string scoreDisplay;
};

