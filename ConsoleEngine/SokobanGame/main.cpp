#include "Game/Game.h"
#include "Scene/GameScene.h"

using namespace std;

int main() {
	CheckMemoryLeak();

	Engine engine;
	engine.LoadScene(new GameScene());
	engine.Run();
	return 0;
}