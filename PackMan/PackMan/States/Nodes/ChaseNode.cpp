#include "ChaseNode.h"
#include "States/BlackBoard.h"
#include "States/IMoveable.h"
#include "Scene/GameScene.h"
#include "Entity/DrawableEntity.h"
#include "Engine/Engine.h"

ChaseNode::ChaseNode(BlackBoard* blackBoard)
    : INode(blackBoard)
{
}

ChaseNode::~ChaseNode()
{
}

bool ChaseNode::CheckCondition()
{
    blackBoard->entity->SetColor(Color::BrightRed);
    blackBoard->speed = 6;
    return IsInBoundary();
}

void ChaseNode::Update(float deltaTime)
{
    Vector2 newPos = blackBoard->entity->GetPosition() + blackBoard->dir * deltaTime * blackBoard->speed;
    if (blackBoard->scene->CanMove(newPos)) {
        blackBoard->entity->SetPosition(newPos);
    }
}

void ChaseNode::Clear()
{
    nodeStates = ENodeStates::Stop;
}

bool ChaseNode::Check(Vector2 searchedPos, const Vector2& dir, const Vector2& targetPos, int depth)
{
    if (!depth) return false;
    searchedPos += dir;
    if (!blackBoard->scene->CanMove(searchedPos)) return false;
    
    if (searchedPos.IntCompare(targetPos)) return true;

    return Check(searchedPos, dir, targetPos, --depth);
}

bool ChaseNode::IsInBoundary()
{
    Vector2 targetPos = blackBoard->target->GetPosition();
    Vector2 currentPos = blackBoard->entity->GetPosition().GetIntVector2();

    //재귀 전 일자로 체크
    if (targetPos.GetX() - currentPos.GetX() <= depth || currentPos.GetX() - targetPos.GetX() <= depth) {

        if (Check(currentPos, Vector2::Left, targetPos, depth)) {
            blackBoard->dir = Vector2::Left;
            nodeStates = ENodeStates::Run;
            return true;
        }

        if (Check(currentPos, Vector2::Right, targetPos, depth)) {
            blackBoard->dir = Vector2::Right;
            nodeStates = ENodeStates::Run;
            return true;
        }
    }

    if (targetPos.GetY() - currentPos.GetY() <= depth || currentPos.GetY() - targetPos.GetY() <= depth) {
        
        if (Check(currentPos, Vector2::Up, targetPos, depth)) {
            blackBoard->dir = Vector2::Up;
            nodeStates = ENodeStates::Run;
            return true;
        }

        if (Check(currentPos, Vector2::Down, targetPos, depth)) {
            blackBoard->dir = Vector2::Down;
            nodeStates = ENodeStates::Run;
            return true;
        }
    }

    return false;
}
