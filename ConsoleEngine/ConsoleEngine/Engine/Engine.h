#pragma once

class Engine
{
public:
	Engine();
	virtual ~Engine();

	void Run();

protected:
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

	bool quit = false;
};

