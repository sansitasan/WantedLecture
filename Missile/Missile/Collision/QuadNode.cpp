#include "QuadNode.h"
#include "QuadTree.h"
#include "Core.h"

QuadNode::QuadNode(const Bound& bound, int depth, std::wstring image)
    : bound(bound), depth(depth), Super(bound.LeftUp(), image)
{
    SetColor(Color::BrightGreen);
}

QuadNode::~QuadNode()
{
    Clear();
}

void QuadNode::Insert(const Vector2& player)
{
    ENodeIndex result = TestRegion(player);
    if (result == ENodeIndex::OutOfArea) return;

    isInPlayer = true;
    if (result == ENodeIndex::Straddling) {
        playerPosition = &player;
    }

    else if (result != ENodeIndex::OutOfArea) {
        if (SubDivide()) child[(int)result]->Insert(player);
        else playerPosition = &player;
    }
}

void QuadNode::Remove()
{
    if (!isInPlayer) return;
    playerPosition = nullptr;
    if (IsDivided()) {
        for (int i = 0; i < (int)EDir::Size; ++i) {
            child[i]->Remove();
        }
    }
}

bool QuadNode::IsMouseNear(const Vector2& other, Vector2& playerPosition)
{
    if (!isInPlayer) return false;

    if (this->playerPosition) {
        playerPosition = *this->playerPosition;
        return true;
    }

    if (IsDivided()) {
        std::vector<ENodeIndex> quads = GetQuads(other);

        for (ENodeIndex& index : quads) {
            if (child[(int)index]->IsMouseNear(other, playerPosition)) return true;
        }
    }

    __debugbreak();
    return false;
}

void QuadNode::Clear()
{
    playerPosition = nullptr;

    if (IsDivided()) {
        for (int i = 0; i < (int)EDir::Size; ++i) {
            child[i]->Clear();
        }

        ClearChildren();
    }
}

void QuadNode::Draw()
{
}

inline bool QuadNode::SubDivide()
{
    if (depth == QuadTree::maxDepth) return false;

    if (!IsDivided()) {
        const Vector2& leftUp = bound.LeftUp();
        const Vector2& rightBottom = bound.RightBottom();
        Vector2 halfVector = rightBottom * 0.5f;

        child[(int)EDir::TopLeft] = new QuadNode(Bound(leftUp, halfVector), depth + 1);
        child[(int)EDir::TopRight] = new QuadNode(Bound(Vector2(leftUp.GetX() + halfVector.GetX(), halfVector.GetY()), halfVector), depth + 1);
        child[(int)EDir::BottomLeft] = new QuadNode(Bound(Vector2(leftUp.GetX(), leftUp.GetY() + halfVector.GetY()), Vector2(leftUp.GetX() + halfVector.GetX(), rightBottom.GetY())), depth + 1);
        child[(int)EDir::BottomRight] = new QuadNode(Bound(halfVector, rightBottom), depth + 1);
    }
    return true;
}

inline bool QuadNode::IsDivided()
{
    return child[(int)EDir::TopLeft] != nullptr;
}

inline void QuadNode::ClearChildren()
{
    if (IsDivided()) {
        for (int i = 0; i < (int)EDir::Size; ++i) {
            SafeDelete(&child[i]);
        }
    }
}

inline ENodeIndex QuadNode::TestRegion(const Vector2& player)
{
    std::vector<ENodeIndex> quads = GetQuads(player);

    if (!quads.size()) return ENodeIndex::OutOfArea;
    if (quads.size() == 1) return quads[0];

    return ENodeIndex::Straddling;
}

inline std::vector<ENodeIndex> QuadNode::GetQuads(const Vector2& player)
{
    std::vector<ENodeIndex> quads;

    //영역 계산에 필요한 변수
    const Vector2& leftUp = bound.LeftUp();
    const Vector2& rightBottom = bound.RightBottom();
    Vector2 half = bound.RightBottom() * 0.5f;

    //영역 확인
    bool left = player.GetX() < half.GetX() && player.GetX() >= leftUp.GetX();
    bool right = player.GetX() >= half.GetX() && player.GetX() < rightBottom.GetX();

    bool top = player.GetY() < half.GetY() && player.GetY() >= leftUp.GetY();
    bool bottom = player.GetY() >= half.GetY() && player.GetY() < rightBottom.GetY();

    if (top && left) {
        quads.emplace_back(ENodeIndex::TopLeft);
    }
    if (top && right) {
        quads.emplace_back(ENodeIndex::TopRight);
    }
    if (bottom && left) {
        quads.emplace_back(ENodeIndex::BottomLeft);
    }
    if (bottom && right) {
        quads.emplace_back(ENodeIndex::BottmRight);
    }

    return quads;
}
