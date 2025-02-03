#pragma once
#include <Entity/DrawableEntity.h>
#include "States/IMoveable.h"

class GameScene;

class Player : public DrawableEntity, public IMoveable
{
	RTTI_DECLARATIONS(Player, DrawableEntity)
public:
	Player(const Vector2& position, GameScene* gameScene);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Destroy() override;

	virtual EState GetState() const override;
	virtual inline Vector2 GetPosition() const override;

	void GetItem(class Item& item);
	inline float GetSpeed() const { return currentSpeed; }
private:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void SetStateOrigin();
	Vector2 moveDir;

	int itemCount = 0;
	int originSpeed;
	float currentSpeed;

	GameScene* gameScene;
	EState currentState;
};

