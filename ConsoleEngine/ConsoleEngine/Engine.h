#pragma once

#define KEYCOUNT 255

struct KeyState {
	//�� �� �־�� Ű�� ���������� Ȯ���� �����ϴ�
	bool isKeyDown = false;
	bool wasKeyDown = false;
};

class Engine
{
public:
	Engine();
	virtual ~Engine();

	void Run();

	//���� ���ȴ��� Ȯ��
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
};

