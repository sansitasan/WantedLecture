#include "GameScene.h"
#include "Engine/Engine.h"
#include "Entity/Wall.h"
#include "Entity/Player.h"
#include "Entity/Food.h"
#include "Entity/Item.h"
#include "Entity/Enemy.h"
#include "Manager/DataManager.h"

GameScene::GameScene(const DataManager& dataManager)
    : score(0)
{
    scoreDisplay.append("Score: ");
    std::vector<std::vector<std::pair<int, int>>> counts(6);
    Engine::Get().SetCursorType(ECursorType::NoCursor);
    map = dataManager.GetMap(width, height);
    int x = 0, y = 0;
    bool isPlayerGenerate = false;
    entityMap = TraceNew DrawableEntity*[(width - 1) * height + 1];
    memset(entityMap, 0, sizeof(DrawableEntity*) * ((width - 1) * height) + 1);
    DrawableEntity* entity = nullptr;
    
    for (int i = 0; i < map.length(); ++i) {
        if (map[i] == '\n') {
            x = 0;
            ++y;
            continue;
        }

        if (!map[i]) break;

        if (map[i] != '0') counts[map[i] - '0'].push_back(std::make_pair(x, y));
        
        if (map[i] - '0' == (int)EEntitys::Player && !isPlayerGenerate) {
            player = TraceNew Player(Vector2(x, y), this);
            isPlayerGenerate = true;
            AddEntity(player);
        }

        ++x;
    }

    foodAndItemCounts = (int)(counts[(int)EEntitys::Food].size() + counts[(int)EEntitys::Item].size());
    enemies = std::vector<Enemy*>(counts[(int)EEntitys::Enemy].size());

    for (int i = 1; i < 6; ++i) {
        for (int j = 0; j < counts[i].size(); ++j) {
            x = counts[i][j].first;
            y = counts[i][j].second;
    
            switch (i) {
            case (int)EEntitys::Wall:
                entity = TraceNew Wall(Vector2(x, y));
                break;
    
            case (int)EEntitys::Food:
                entity = TraceNew Food(Vector2(x, y));
                break;
    
            case (int)EEntitys::Enemy:
                enemies[j] = TraceNew Enemy(Vector2(x, y), this, player);
                entity = enemies[j];
                break;
    
            case (int)EEntitys::Item:
                entity = TraceNew Item(Vector2(x, y));
                break;
    
            case (int)EEntitys::Player:
                map[x + width * y] = ' ';
                break;
    
            default:
                map[x + width * y] = ' ';
                break;
            }
    
            entityMap[x + y * (width - 1)] = entity;
            if (entity) AddEntity(entity);
            entity = nullptr;
        }
    }
}

GameScene::~GameScene()
{
    delete[] entityMap;
    entityMap = nullptr;
    enemies.clear();
}

void GameScene::Update(float deltaTime)
{
    if (isClear) return;

    Super::Update(deltaTime);
    CollisionEnemyAndPlayer();
}

void GameScene::Draw()
{
    if (isClear) {
        Engine::Get().Draw(Vector2(width >> 1, height >> 1), scoreDisplay.c_str(), Color::BrightWhite);
        Engine::Get().Draw(Vector2((width >> 1) + (int)scoreDisplay.length(), height >> 1), std::to_string(score).c_str(), Color::BrightWhite);
        return;
    }

    Engine::Get().SetCursorPosition(0, 0);
    Super::Draw();

    for (int i = 0; i < enemies.size(); ++i) {
        enemies[i]->Draw();
    }

    Engine::Get().Draw(Vector2(0, 0), scoreDisplay.c_str(), Color::BrightWhite);
    Engine::Get().Draw(Vector2((int)scoreDisplay.length(), 0), std::to_string(score).c_str(), Color::BrightWhite);
    Engine::Get().Draw(Vector2((int)scoreDisplay.length() + 5, 0), "FPS: ", Color::BrightWhite);
    float t = Engine::Get().GetFPS();
    Engine::Get().Draw(Vector2((int)scoreDisplay.length() + 10, 0), std::to_string(t).c_str(), Color::BrightWhite);
}

void GameScene::ChangeX(Vector2& position) {
    if (position.GetX() >= width - 1) {
        position = Vector2((position.GetX() - width + 1), position.GetY());
    }
    else if (position.GetX() < 0) {
        position = Vector2((float)width - 1.1f, position.GetY());
    }
}

bool GameScene::CanMove(Vector2& position, Entity* entity)
{
    if (position.GetX() >= width - 1) {
        position = Vector2((position.GetX() - width + 1), position.GetY());
    }
    else if (position.GetX() < 0) {
        position = Vector2((float)width - 1.1f, position.GetY());
    }
    if (map.size() < (int)position.GetX() + width * (int)position.GetY()) return false;

    char t = map[(int)position.GetX() + width * (int)position.GetY()] - '0';
    if (t == (char)EEntitys::Wall) return false;

    if (entity != player) {

        return true;
    }

    switch (t) {
        case (char)EEntitys::Food:
            map[(int)position.GetX() + width * (int)position.GetY()] = ' ';
            Engine::Get().DestroyEntity(entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()]);
            entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()] = nullptr;
            score += 10;
            --foodAndItemCounts;
            break;

        case (char)EEntitys::Item: 
            map[(int)position.GetX() + width * (int)position.GetY()] = ' ';
            Item* item = entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()]->As<Item>();
            if (item) player->GetItem(*item);
            Engine::Get().DestroyEntity(entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()]);
            entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()] = nullptr;
            score += 50;
            --foodAndItemCounts;
            break;
    }

    IsGameClear();

    return true;
}

bool GameScene::IsGameClear()
{
    if (!foodAndItemCounts || !player) {
        isClear = true;
        COROUTINE(EndGame, GameScene, 3, false);
    }
    return isClear;
}

void GameScene::EndGame()
{
    Engine::Get().QuitEngine();
}

void GameScene::CollisionEnemyAndPlayer()
{
    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->GetPosition().IntCompare(player->GetPosition())) {
            if (player->GetState() == EState::Normal) {
                Engine::Get().DestroyEntity(player);
                player = nullptr;
                IsGameClear();
                break;
            }

            score += 200;
            Engine::Get().DestroyEntity(enemies[i]);
            enemies.erase(enemies.begin() + i);
            --i;
        }
    }
}
