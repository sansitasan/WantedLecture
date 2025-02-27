#include <iostream>
#include "Engine/GameEngine.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetBreakAlloc(155);
	GameEngine* engine = TraceNew GameEngine();

    engine->LoadScene();

	engine->Run();
    delete engine;
    _CrtDumpMemoryLeaks();

	return 0;
}