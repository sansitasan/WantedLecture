#pragma once
#include "Core.h"

#define KEYCOUNT 255

struct KeyState {
	//�� �� �־�� Ű�� ���������� Ȯ���� �����ϴ�
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

	//���� ���ȴ��� Ȯ��
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
	//Ÿ�� ������ ����
	float targetFrameRate;
	float targetOneFrameTime;
	bool quit = false;

	KeyState keyState[KEYCOUNT];

	void (*delegateKeyDown[KEYCOUNT])();
	void (*delegateKey[KEYCOUNT])();
	void (*delegateKeyUp[KEYCOUNT])();

	static Engine* instance;

	//Scene�� ������ �ö������ �� �ִ�
	Scene* mainScene;
};

