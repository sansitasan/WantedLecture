#include "PreCompiledHeader.h"
#include "Core.h"
#include "Engine/Engine.h"
#include "Math/Vector/Vector2.h"

using namespace std;

//RTTI - RunTime Type Information
//PCH - PreCompiledHeader
//DLL - 자동화 완료

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Engine& engine = Engine::Get(35, 40, 16, 16);
	engine.Run();
	delete &engine;
	_CrtDumpMemoryLeaks();

	return 0;
}