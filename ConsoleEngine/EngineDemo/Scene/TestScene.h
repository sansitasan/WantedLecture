#pragma once
#include "Scene/Scene.h"

class TestScene : public Scene
{
	RTTI_DECLARATIONS(TestScene, Scene)

public:
	TestScene();
	virtual ~TestScene() override;

	virtual void Update(float deltaTime) override;
};

