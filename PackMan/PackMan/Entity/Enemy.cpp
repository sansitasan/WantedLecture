#include "Enemy.h"
#include "Scene/GameScene.h"
#include "States/BT.h"
#include "States/Nodes/MoveNode.h"
#include "States/Nodes/ChaseNode.h"
#include "States/Nodes/RunNode.h"
#include "States/IMoveable.h"

Enemy::Enemy(const Vector2& position, GameScene* gameScene, IMoveable* player)
	: Super("E"), gameScene(gameScene), spawnPosition(position)
{
	this->position = position;
	this->position += Vector2(0.5f, 0.5f);
	entityColor = Color::BrightRed;
	bt = TraceNew BehaviorTree(this, player, gameScene, 6);
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
	RunNode* run = TraceNew RunNode(bt->GetBlackBoard());
	bt->AddNode(*run);
	ChaseNode* chase = TraceNew ChaseNode(bt->GetBlackBoard());
	bt->AddNode(*chase);
	MoveNode* move = TraceNew MoveNode(bt->GetBlackBoard());
	bt->AddNode(*move);
}
