#include "ChaseNode.h"
#include "States/BlackBoard.h"
#include "States/IMoveable.h"
#include "Scene/GameScene.h"
#include "Engine/Engine.h"

ChaseNode::ChaseNode(BlackBoard* blackBoard)
{
}

ChaseNode::~ChaseNode()
{
}

bool ChaseNode::CheckCondition()
{
    return (blackBoard->target->GetState() == EState::Normal) && IsInBoundary();
}

void ChaseNode::Update(float deltaTime)
{

}

bool ChaseNode::IsInBoundary()
{
    Vector2 targetPos = blackBoard->target->GetPosition();
    //blackBoard->scene->CanMove()
    return false;
}
