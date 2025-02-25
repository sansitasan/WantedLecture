#pragma once
#include <functional>
#include <vector>
#include "Core.h"
#include "Math/Vector/Vector2.h"

#define KEYCOUNT 255
#pragma warning( disable : 4251 )

class TimerManager;

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
	//타겟 프레임 변수
	float targetFrameRate;
	float targetOneFrameTime;
	bool quit = false;
	bool shouldUpdate = true;

	KeyState keyState[KEYCOUNT];

	//Scene이 여러개 올라와있을 수 있다
	Scene* mainScene;

	Vector2 screenSize;

	// 마우스 좌표 위치.
	Vector2 mousePosition;

	char* emptyStringBuffer = nullptr;

	//DX에서는 버퍼를 Buffer/Blob 두 가지 용어를 쓰는데 Blob = 덩어리라는 뜻

	TimerManager* timerManager;

	// 화면 지울 때 사용할 버퍼(Buffer/Blob).
	CHAR_INFO* imageBuffer = nullptr;

	// 화면 버퍼.
	ScreenBuffer* renderTargets[2];
	int currentRenderTargetIndex = 0;

private:
	static Engine* instance;
	Delegate delegateKeyDown;
	Delegate delegateKey;
	Delegate delegateKeyUp;

	float deltaTime;
};