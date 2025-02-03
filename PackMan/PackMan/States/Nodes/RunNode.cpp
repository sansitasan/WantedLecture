#include "RunNode.h"
#include "States/BlackBoard.h"
#include "States/IMoveable.h"
#include "Scene/GameScene.h"
#include "Entity/DrawableEntity.h"
#include "Engine/Engine.h"

RunNode::RunNode(BlackBoard* blackBoard)
    : INode(blackBoard)
{
    nextPos = Vector2::Zero;
    originSpeed = blackBoard->speed;
}

RunNode::~RunNode()
{
}

bool RunNode::CheckCondition()
{
    if (blackBoard->target->GetState() == EState::Super) {
        nodeStates = ENodeStates::Run;
        blackBoard->speed = originSpeed * 0.5f;
        blackBoard->entity->SetColor(Color::Blue);
        return true;
    }
    Clear();
    return false;
}

void RunNode::Update(float deltaTime)
{
    Vector2 originPos = blackBoard->entity->GetPosition();

    if (nextPos != Vector2::Zero && !originPos.IntCompare(nextPos)) {
        originPos += blackBoard->dir * deltaTime * blackBoard->speed;
        blackBoard->scene->ChangeX(originPos);
        blackBoard->entity->SetPosition(originPos);
        return;
    }

    Vector2 targetPos = blackBoard->target->GetPosition().GetIntVector2();

    FindRoute(targetPos, originPos);
}

void RunNode::Clear()
{
    nextPos = Vector2::Zero;
    nodeStates = ENodeStates::Stop;
}

inline void RunNode::FindRoute(const Vector2& targetPos, const Vector2& originPos)
{
    int max = -1, temp = 0;

    Vector2 comparePos = originPos;
    SetnextPos(targetPos, comparePos, Vector2::Zero, max);
    SetnextPos(targetPos, comparePos, Vector2::Up, max);
    SetnextPos(targetPos, comparePos, Vector2::Down, max);
    SetnextPos(targetPos, comparePos, Vector2::Right, max);
    SetnextPos(targetPos, comparePos, Vector2::Left, max);
}

inline void RunNode::SetnextPos(const Vector2& targetPos, Vector2 nearPos, const Vector2& dir, int& max)
{
    int temp = 0;
    nearPos = (nearPos + dir).GetIntVector2();
    if (blackBoard->scene->CanMove(nearPos)) {
        temp = CheckManhattanDistance(targetPos, nearPos);
        if (temp > max) {
            nextPos = nearPos;
            max = temp;
            blackBoard->dir = dir;
        }
    }
}

inline int RunNode::CheckManhattanDistance(const Vector2& targetPos, const Vector2& comparePos)
{
    return abs((int)targetPos.GetX() - (int)comparePos.GetX()) + abs((int)targetPos.GetY() - (int)comparePos.GetY());
}
