#include "QuadNode.h"
#include "QuadTree.h"
#include "Core.h"
#include <Engine/Engine.h>

const std::wstring QuadNode::image = TEXT("#");

QuadNode::QuadNode(const Bound& bound, int depth)
    : bound(bound), depth(depth)
{
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
    isInPlayer = false;
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
            if (child[(int)index]->IsMouseNear(other, playerPosition)) {
                if (playerPosition.GetX() == -1) __debugbreak();
                return true;
            }
        }
    }

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

void QuadNode::Draw(unsigned short executeLayer)
{
    const Vector2& leftUp = bound.LeftUp();
    const Vector2& rightBottom = bound.RightBottom();
    int end = (int)rightBottom.GetX();

    for (int i = (int)leftUp.GetX(); i < end; ++i) {
        Engine::Get().Draw(i, (int)leftUp.GetY(), image, color);
        Engine::Get().Draw(i, (int)rightBottom.GetY() - 1, image, color);

        if (i == 103) {
            int x = 1;
        }
    }

    end = (int)rightBottom.GetY();

    for (int i = (int)leftUp.GetY() + 1; i < end; ++i) {
        Engine::Get().Draw((int)leftUp.GetX(), i, image, color);
        Engine::Get().Draw((int)rightBottom.GetX() - 1, i, image, color);
    }

    //if (_heapchk() != _HEAPOK)
    //{
    //    __debugbreak();
    //}

    if (IsDivided()) {
        for (int i = 0; i < (int)EDir::Size; ++i) {
            child[i]->Draw(executeLayer);
        }
    }

    if (executeLayer & (unsigned short)EExecuteLayer::QuadTreePositionDraw) {

        Vector2 vec = (bound.WidthAndHeight() * 0.5f) + leftUp;
        vec -= Vector2::Up;

        wchar_t buffer[255] = {};
        _snwprintf_s(buffer, 255, L"%d, %d", (int)leftUp.GetX(), (int)leftUp.GetY());
        Engine::Get().Draw(vec - Vector2(wcslen(buffer) * 0.5f, 0.f), buffer, color);
        vec += Vector2::Up;
        _snwprintf_s(buffer, 255, L"%d, %d", (int)vec.GetX(), (int)vec.GetY());
        Engine::Get().Draw(vec - Vector2(wcslen(buffer) * 0.5f, 0.f), buffer, color);
        vec += Vector2::Up;
        _snwprintf_s(buffer, 255, L"%d, %d", (int)rightBottom.GetX(), (int)rightBottom.GetY());
        Engine::Get().Draw(vec - Vector2(wcslen(buffer) * 0.5f, 0.f), buffer, color);
    }
}

inline bool QuadNode::SubDivide()
{
    if (depth == QuadTree::maxDepth) return false;

    if (!IsDivided()) {
        const Vector2& leftUp = bound.LeftUp();
        const Vector2& rightBottom = bound.RightBottom();
        Vector2 halfVector = (bound.WidthAndHeight() * 0.5f) + leftUp;

        child[(int)EDir::TopLeft] = new QuadNode(Bound(leftUp, halfVector), depth + 1);
        child[(int)EDir::TopRight] = new QuadNode(Bound(Vector2(halfVector.GetX(), leftUp.GetY()), Vector2(rightBottom.GetX(), halfVector.GetY())), depth + 1);
        child[(int)EDir::BottomLeft] = new QuadNode(Bound(Vector2(leftUp.GetX(), halfVector.GetY()), Vector2(halfVector.GetX(), rightBottom.GetY())), depth + 1);
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
    Vector2 half = (bound.WidthAndHeight() * 0.5f) + leftUp;

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
