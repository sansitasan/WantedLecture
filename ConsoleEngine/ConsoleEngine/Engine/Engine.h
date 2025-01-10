#pragma once
#include <functional>
#include <vector>
#include "Core.h"

#define KEYCOUNT 255

struct KeyState {
	//둘 다 있어야 키가 유지중인지 확인이 가능하다
	bool isKeyDown = false;
	bool wasKeyDown = false;
};

enum class ECursorType {
	NoCursor,
	SolidCursor,
	NormalCursor
};

class Scene;
class Entity;

class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	static Engine& Get();

	void Run();

	void LoadScene(Scene* newScene);

	void AddEntity(Entity* entity);
	void DestroyEntity(Entity* entity);

	void SetCursorType(ECursorType type);
	void SetCursorPosition(const struct Vector2& position);
	void SetCursorPosition(int x, int y);

	void SetTargetFrameRate(float targetFrameRate);

	//현재 눌렸는지 확인
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	void QuitEngine();

	void SubscribeGetKey(std::function<void()>, int key);
	void SubscribeGetKeyDown(std::function<void()>, int key);
	void SubscribeGetKeyUp(std::function<void()>, int key);

	void UnSubscribeGetKey(std::function<void()>, int key);
	void UnSubscribeGetKeyDown(std::function<void()>, int key);
	void UnSubscribeGetKeyUp(std::function<void()>, int key);

protected:
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();
	void Clear();

protected:
	//타겟 프레임 변수
	float targetFrameRate;
	float targetOneFrameTime;
	bool quit = false;
	bool shouldUpdate = true;

	KeyState keyState[KEYCOUNT];

	std::vector<std::vector<std::function<void()>>> delegateKeyDown;
	std::vector<std::vector<std::function<void()>>> delegateKey;
	std::vector<std::vector<std::function<void()>>> delegateKeyUp;

	static Engine* instance;

	//Scene이 여러개 올라와있을 수 있다
	Scene* mainScene;
};

