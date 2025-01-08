#pragma once
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

class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	static Engine& Get();

	void Run();

	void LoadScene(Scene* newScene);

	void SetCursorType(ECursorType type);
	void SetCursorPosition(const struct Vector2& position);
	void SetCursorPosition(int x, int y);

	void SetTargetFrameRate(float targetFrameRate);

	//현재 눌렸는지 확인
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	void QuitEngine();

	void SubscribeGetKey(void(*delegate)(), int key);
	void SubscribeGetKeyDown(void(*delegate)(), int key);
	void SubscribeGetKeyUp(void(*delegate)(), int key);

	void UnSubscribeGetKey(void(*delegate)(), int key);
	void UnSubscribeGetKeyDown(void(*delegate)(), int key);
	void UnSubscribeGetKeyUp(void(*delegate)(), int key);

protected:
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

protected:
	//타겟 프레임 변수
	float targetFrameRate;
	float targetOneFrameTime;
	bool quit = false;

	KeyState keyState[KEYCOUNT];

	void (*delegateKeyDown[KEYCOUNT])();
	void (*delegateKey[KEYCOUNT])();
	void (*delegateKeyUp[KEYCOUNT])();

	static Engine* instance;

	//Scene이 여러개 올라와있을 수 있다
	Scene* mainScene;
};

