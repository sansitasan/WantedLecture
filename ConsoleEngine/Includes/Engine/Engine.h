#pragma once
#include "Core.h"

#define KEYCOUNT 255

struct KeyState {
	//�� �� �־�� Ű�� ���������� Ȯ���� �����ϴ�
	bool isKeyDown = false;
	bool wasKeyDown = false;
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
	void Update(double deltaTime);
	void Draw();

protected:
	bool quit = false;

	KeyState keyState[KEYCOUNT];

	void (*delegateKeyDown[KEYCOUNT])();
	void (*delegateKey[KEYCOUNT])();
	void (*delegateKeyUp[KEYCOUNT])();

	static Engine* instance;

	//Scene�� ������ �ö������ �� �ִ�
	Scene* mainScene;
};

