#include "PreCompiledHeader.h"
#include "Core.h"
#include "Engine/Engine.h"
#include "Vector/Vector2.h"

using namespace std;

//RTTI - RunTime Type Information
//PCH - PreCompiledHeader
//DLL ¿¹Á¤

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Engine engine;
	engine.Run();
	_CrtDumpMemoryLeaks();
	return 0;
}