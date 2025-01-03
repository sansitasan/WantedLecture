#pragma once

#define KEYCOUNT 255

struct ENGINE_API KeyState {
	//둘 다 있어야 키가 유지중인지 확인이 가능하다
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

	//현재 눌렸는지 확인
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	void QuitEngine();

protected:
	void ProcessInput();
	void Update(double deltaTime);
	void Draw();

protected:
	bool quit = false;

	KeyState keyState[KEYCOUNT];

	static Engine* instance;

	//Scene이 여러개 올라와있을 수 있다
	Scene* mainScene;
};

