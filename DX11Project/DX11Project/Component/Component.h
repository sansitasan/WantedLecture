#pragma once

namespace SanDX {
    class Component
    {
    public:
        Component();
        virtual ~Component();

        virtual void BeginPlay();
        virtual void Update(float deltaTime);
        virtual void Draw();

        class Entity* GetOwner() const;
        void SetOwner(class Entity* newOnwer);

    protected:
        class Entity* owner = nullptr;
    };
}