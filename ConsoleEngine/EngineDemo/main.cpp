#include "Game/Game.h"
#include "Scene/TestScene.h"

using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	game.LoadScene(new TestScene());
	game.Run();
	_CrtDumpMemoryLeaks();
	return 0;
}