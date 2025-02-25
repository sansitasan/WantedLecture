#pragma once
#include "Bound.h"
#include <Entity/DrawableEntity.h>

enum class ENodeIndex {
    TopLeft,	//영역에 포함된 것
    TopRight,
    BottomLeft,
    BottmRight,
    Straddling,	//경계선에 걸친 것
    OutOfArea	//영역을 벗어난 것
};

enum class EDir {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    Size
};

class QuadNode : public DrawableEntity {
    RTTI_DECLARATIONS(QuadNode, DrawableEntity)
public:
    QuadNode(const Bound& bound, int depth = 0, std::wstring image = TEXT("#"));
    ~QuadNode();

    void Insert(const Vector2& player);

    void Remove();

    bool IsMouseNear(const Vector2& other, Vector2& playerPosition);

    void Clear();

    inline QuadNode* Child(EDir dir) const { return child[(int)dir]; }

    inline int Depth() const { return depth; }

    virtual void Draw() override;

private:
    //영역 분할시 사용
    inline bool SubDivide();

    //영역 분할 확인
    inline bool IsDivided();

    inline void ClearChildren();

    //전달한 영역과 겹치는 영역을 반환
    inline ENodeIndex TestRegion(const Vector2& player);

    //전달한 영역이 포함되거나 걸치는 영역을 모두 구하는 함수
    inline std::vector<ENodeIndex> GetQuads(const Vector2& player);

private:
    Bound bound;
    QuadNode* child[4] = {};
    //현재 노드의 깊이
    int depth = 0;
    
    bool isInPlayer = false;
    
    const Vector2* playerPosition = nullptr;
};