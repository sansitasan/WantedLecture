#include "MoveNode.h"
#include "States/BlackBoard.h"
#include "Entity/Entity.h"
#include "Scene/GameScene.h"
#include "Engine/Engine.h"
#include "Core.h"

MoveNode::MoveNode(BlackBoard* blackBoard)
    : INode(blackBoard)
{
    currentDir = (EDir)Random(0, 3);
    SetMoveDir((int)currentDir);
    nextPos = Vector2::Zero;
}

MoveNode::~MoveNode()
{
    delete[] dir;
}

bool MoveNode::CheckCondition()
{
    return true;
}

void MoveNode::Update(float deltaTime)
{
    Vector2 originPos = blackBoard->entity->GetPosition();

    if (nextPos != Vector2::Zero && ((int)originPos.GetX() != (int)nextPos.GetX() || (int)originPos.GetY() != (int)nextPos.GetY())) {
        originPos += moveDir * deltaTime * speed;
        blackBoard->scene->ChangeX(originPos);
        blackBoard->entity->SetPosition(originPos);
        return;
    }

    Vector2 tempPos = originPos + (moveDir * deltaTime * speed);
    Vector2 t = originPos + moveDir;
    bool canMove[4] = { 0, };
    Vector2 vec[4];
    int temp = (int)currentDir;
    int idx = 0;

    for (int i = 0; i < 4; ++i) {
        canMove[i] = blackBoard->scene->CanMove(t, blackBoard->entity);
        vec[i] = t;
        temp = (dir[i] + temp) % 4;
        SetMoveDir(temp);
        tempPos = originPos + (moveDir * deltaTime * speed);
        t = originPos + moveDir;
    }

    if (canMove[1] || canMove[2]) {
        idx = RandomDir(canMove);
    }
    SetMoveDir((int)currentDir);
    tempPos = originPos + moveDir * deltaTime * speed;
    blackBoard->scene->ChangeX(tempPos);
    t = originPos + moveDir;
    nextPos = Vector2((int)vec[idx].GetX(), (int)vec[idx].GetY());
    blackBoard->entity->SetPosition(tempPos);
}

void MoveNode::SetDirRandomly()
{
    int rand = Random(0, 100);
    if (rand < 85) {
        return;
    }
    
    if (rand < 90) {
        currentDir = (EDir)(((int)currentDir + 1) % 4);
    }

    else if (rand < 95){
        currentDir = (EDir)(((int)currentDir + 2) % 4);
    }

    else {
        currentDir = (EDir)(((int)currentDir + 3) % 4);
    }

    SetMoveDir((int)currentDir);
}

void MoveNode::SetMoveDir(int num)
{
    if (!num) {
        moveDir = Vector2::Left;
    }
    else if (num == 1) {
        moveDir = Vector2::Up;
    }
    else if (num == 2) {
        moveDir = Vector2::Right;
    }
    else if (num == 3) {
        moveDir = Vector2::Down;
    }
}

int MoveNode::RandomDir(const bool* canMove)
{
    std::vector<short> vec(4, -1);
    double pro[4] = { 0, };
    double cumul[4] = { 0, };
    double total = 0;

    if (canMove[0]) {
        pro[0] = (double)ERand::First * 0.01f;
        vec[0] = 0;
    }

    if (canMove[1]) { 
        pro[1] = (double)ERand::Second * 0.01f; 
        vec[1] = 1;
    }

    if (canMove[2]) {
        pro[2] = (double)ERand::Third * 0.01f;
        vec[2] = 3;
    }

    if (canMove[3]) {
        pro[3] = (double)ERand::Fourth * 0.01f;
        vec[3] = 2;
    }

    for (short i = 0; i < 4; ++i) {
        total += pro[i];
    }

    for (short i = 0; i < 4; ++i) {
        pro[i] /= total;
    }

    cumul[0] = pro[0];
    for (short i = 1; i < 4; ++i) {
        cumul[i] = cumul[i - 1] + pro[i];
    }

    double randVal = RandomPercent();

    for (short i = 0; i < 4; ++i) {
        if (randVal <= cumul[i]) {
            currentDir = (EDir)(((short)currentDir + vec[i]) % 4);
            return i;
        }
    }

    currentDir = (EDir)(((short)currentDir + vec[vec.size() - 1]) % 4);
    return 3;
}
