#include "CollisionNode.h"
#include "States/BlackBoard.h"
#include "States/IMoveable.h"
#include "Scene/GameScene.h"
#include "Entity/Entity.h"
#include "Engine/Engine.h"

CollisionNode::CollisionNode(BlackBoard* blackBoard)
{
}

CollisionNode::~CollisionNode()
{
}

bool CollisionNode::CheckCondition()
{
    return blackBoard->target->GetPosition().IntCompare(blackBoard->entity->GetPosition());
}

void CollisionNode::Update(float deltaTime)
{
    if (blackBoard->target->GetState() == EState::Super) {
        
        return;
    }

    //TODO: ∞‘¿” ≥°
}
