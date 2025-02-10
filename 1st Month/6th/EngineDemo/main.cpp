#include "Game/Game.h"
#include "Scene/TestScene.h"

using namespace std;

int main() {
	Game game;
	game.LoadScene(new TestScene());
	game.Run();
	return 0;
}