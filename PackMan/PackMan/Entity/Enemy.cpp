#include "Enemy.h"
#include "Scene/GameScene.h"
#include "States/BT.h"
#include "States/Nodes/MoveNode.h"
#include "States/IMoveable.h"

Enemy::Enemy(const Vector2& position, GameScene* gameScene, IMoveable* player)
	: Super("E"), gameScene(gameScene), spawnPosition(position)
{
	this->position = position;
	entityColor = Color::BrightRed;
	bt = new BehaviorTree(this, player, gameScene);
	MakeBT();
}

Enemy::~Enemy()
{
	delete bt;
	bt = nullptr;
}

void Enemy::Update(float deltaTime)
{
	bt->Update(deltaTime);
}

Vector2 Enemy::GetSpawnPoint() const
{
	return spawnPosition;
}

void Enemy::MakeBT()
{
	MoveNode* node = new MoveNode(bt->GetBlackBoard());
	bt->AddNode(*node);
}
