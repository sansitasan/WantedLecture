#pragma once
#include <functional>
#include <vector>
#include "Core.h"
#include "Math/Vector/Vector2.h"

#define KEYCOUNT 255
#pragma warning( disable : 4251 )

class TimerManager;

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
class Entity;
struct Vector2;
class ScreenBuffer;

class ENGINE_API Engine
{
	using Delegate = std::vector<std::vector<std::pair<Entity*, std::function<void()>>>>;
public:
	virtual ~Engine();

	static Engine& Get(int screenSizeX = 160, int screenSizeY = 90, int fontSizeX = 1, int fontSizeY = 1);

	void Run();

	void LoadScene(Scene* newScene);

	void AddEntity(Entity* entity);
	void DestroyEntity(Entity* entity);

	void SetCursorType(ECursorType type);
	void SetCursorPosition(const struct Vector2& position);
	void SetCursorPosition(int x, int y);

	inline Vector2 GetScreenSize() const { return screenSize; }

	void SetTimer(std::function<void()> delegate, const float time, bool isInterval, size_t id);

	void SetTargetFrameRate(float targetFrameRate);

	void QuitEngine();

	void Draw(const Vector2& position, const char* image, Color color);

	void CancelTimer(std::function<void()> delegate, size_t id);
	void CancelAllTimer(size_t id);

	float GetFPS() const { return 1 / deltaTime; }

#pragma region Input Manage
public:

	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	void SubscribeGetKey(std::function<void()>, Entity* entity, int key);
	void SubscribeGetKeyDown(std::function<void()>, Entity* entity, int key);
	void SubscribeGetKeyUp(std::function<void()>, Entity* entity, int key);

	void UnSubscribeGetKey(std::function<void()>, int key);
	void UnSubscribeGetKeyDown(std::function<void()>, int key);
	void UnSubscribeGetKeyUp(std::function<void()>, int key);
#pragma endregion

protected:
	Engine(int screenSizeX, int screenSizeY, int fontSizeX, int fontSizeY);
	void SetConsoleSizeAndLock(HANDLE handle, int width, int height);
	void UnSubscribe(Delegate& delegateVector, std::function<void()> delegate, int key);
	void DelegateInvoke(Delegate& delegateVector, int key);
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();
	void Clear();
	void Present();
	inline ScreenBuffer* GetRenderer() const { return renderTargets[currentRenderTargetIndex]; }
	void ClearImageBuffer();

protected:
	Engine() = delete;
	//Ÿ�� ������ ����
	float targetFrameRate;
	float targetOneFrameTime;
	bool quit = false;
	bool shouldUpdate = true;

	KeyState keyState[KEYCOUNT];

	//Scene�� ������ �ö������ �� �ִ�
	Scene* mainScene;

	Vector2 screenSize;

	// ���콺 ��ǥ ��ġ.
	Vector2 mousePosition;

	char* emptyStringBuffer = nullptr;

	//DX������ ���۸� Buffer/Blob �� ���� �� ���µ� Blob = ������ ��

	TimerManager* timerManager;

	// ȭ�� ���� �� ����� ����(Buffer/Blob).
	CHAR_INFO* imageBuffer = nullptr;

	// ȭ�� ����.
	ScreenBuffer* renderTargets[2];
	int currentRenderTargetIndex = 0;

private:
	static Engine* instance;
	Delegate delegateKeyDown;
	Delegate delegateKey;
	Delegate delegateKeyUp;

	float deltaTime;
};