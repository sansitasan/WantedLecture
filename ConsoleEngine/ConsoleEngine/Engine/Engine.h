#pragma once
#include <functional>
#include <vector>
#include "Core.h"
#include "Math/Vector/Vector2.h"

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
struct Vector2;


class ENGINE_API Engine
{
	using Delegate = std::vector<std::vector<std::function<void()>>>;
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

	inline Vector2 GetScreenSize() const { return screenSize; }

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

	Delegate delegateKeyDown;
	Delegate delegateKey;
	Delegate delegateKeyUp;

	static Engine* instance;

	//Scene이 여러개 올라와있을 수 있다
	Scene* mainScene;

	Vector2 screenSize;

	char* emptyStringBuffer = nullptr;

	//DX에서는 버퍼를 Buffer/Blob 두 가지 용어를 쓰는데 Blob = 덩어리라는 뜻
};

