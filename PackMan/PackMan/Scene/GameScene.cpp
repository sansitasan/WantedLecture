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
        }

        ++x;
    }

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
                entity = TraceNew Enemy(Vector2(x, y), this, player);
                break;
    
            case (int)EEntitys::Item:
                entity = TraceNew Item(Vector2(x, y));
                break;
    
            case (int)EEntitys::Player:
                entity = player;
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
}

void GameScene::Update(float deltaTime)
{
    Super::Update(deltaTime);
}

void GameScene::Draw()
{
    Engine::Get().SetCursorPosition(0, 0);
    Super::Draw();

    Engine::Get().Draw(Vector2(0, 0), scoreDisplay.c_str(), Color::BrightWhite);
    Engine::Get().Draw(Vector2(scoreDisplay.length(), 0), std::to_string(score).c_str(), Color::BrightWhite);
    Engine::Get().Draw(Vector2(scoreDisplay.length() + 5, 0), "FPS: ", Color::BrightWhite);
    Engine::Get().Draw(Vector2(scoreDisplay.length() + 10, 0), std::to_string(Engine::Get().GetFPS()).c_str(), Color::BrightWhite);
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
            entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()]->Destroy();
            entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()] = nullptr;
            score += 10;
            break;

        case (char)EEntitys::Item: {
            map[(int)position.GetX() + width * (int)position.GetY()] = ' ';
            Item* item = entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()]->As<Item>();
            if (item) player->GetItem(*item);
            entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()]->Destroy();
            entityMap[(int)position.GetX() + (width - 1) * (int)position.GetY()] = nullptr;
            score += 50;
            break;
        }
    }

    return true;
}

bool GameScene::IsGameClear()
{
    return false;
}
