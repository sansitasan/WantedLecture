#include "Game/SGame.h"
#include "Scene/GameScene.h"

using namespace std;

int main() {
	CheckMemoryLeak();

	SGame engine;
	Scene* scene = new GameScene();
	engine.LoadScene(scene);
	engine.Run();
	return 0;
}