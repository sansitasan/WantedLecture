#include "Engine/GameEngine.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameEngine& engine = GameEngine::Get();

	engine.LoadGameScene();
	engine.Run();
	_CrtDumpMemoryLeaks();
	return 0;
}