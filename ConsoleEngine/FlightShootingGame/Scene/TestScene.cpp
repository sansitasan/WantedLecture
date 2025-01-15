#include "TestScene.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Entity/Player.h"
#include "Entity/PlayerBullet.h"
#include "Entity/Enemy.h"
#include "Entity/EnemyBullet.h"
#include <Windows.h>

TestScene::TestScene()
{
	AddEntity(new Player("<P>"));
}

TestScene::~TestScene()
{
}

void TestScene::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE)) {
		Engine::Get().QuitEngine();
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Color::Green);
	Engine::Get().SetCursorPosition(0, Engine::Get().GetScreenSize().GetY() + 3);
	Log("Score: %d", score);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::White);

	SpawnEnemy(deltaTime);

	//충돌 처리
	ProcessCollisionPlayerBulletAndEnemy();
	ProcessCollisionEnemyBulletAndPlayer();
}

void TestScene::SpawnEnemy(float deltaTime)
{
	static float elapsedTime = 0.f;
	static float spawnTime = RandomPercent(1, 3);

	elapsedTime += deltaTime;
	if (elapsedTime < spawnTime) return;

	elapsedTime = 0;

	AddEntity(new Enemy());
}

void TestScene::ProcessCollisionPlayerBulletAndEnemy()
{
	List<PlayerBullet*> bullets;
	List<Enemy*> enemies;

	for (Entity* entity : SceneEntityList) {
		PlayerBullet* bullet = entity->As<PlayerBullet>();
		if (bullet) {
			bullets.PushBack(bullet);
			continue;
		}

		Enemy* enemy = entity->As<Enemy>();
		if (enemy) {
			enemies.PushBack(enemy);
		}
	}

	if (!bullets.Size() || !enemies.Size()) return;
	
	for (PlayerBullet* bullet : bullets) {
		for (Enemy* enemy : enemies) {
			if (!enemy->IsActive()) continue;

			if (bullet->IsIntersect(*enemy)) {
				enemy->Destroy();
				bullet->Destroy();
				++score;
			}
		}
	}
}

void TestScene::ProcessCollisionEnemyBulletAndPlayer()
{
	List<EnemyBullet*> bullets;
	Player* player = nullptr;

	for (Entity* entity : SceneEntityList) {
		EnemyBullet* bullet = entity->As<EnemyBullet>();
		if (bullet) {
			bullets.PushBack(bullet);
			continue;
		}

		if (!player) {
			player = entity->As<Player>();
		}
	}

	if (!bullets.Size() && player && !player->IsActive()) return;

	for (EnemyBullet* bullet : bullets) {
		if (bullet->IsIntersect(*player)) {
			bullet->Destroy();
			player->Destroy();

			Sleep(2000);

			Engine::Get().QuitEngine();
		}
	}
}
