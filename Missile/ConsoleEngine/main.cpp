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
    _CrtMemState s1, s2, s3;
    _CrtMemCheckpoint(&s1);
	Engine& engine = Engine::Get();
	engine.Run();
	delete &engine;
    //_CrtSetBreakAlloc(155);
    _CrtMemCheckpoint(&s2);
    if (_CrtMemDifference(&s3, &s1, &s2))
        _CrtMemDumpStatistics(&s3);
	_CrtDumpMemoryLeaks();

	return 0;
}