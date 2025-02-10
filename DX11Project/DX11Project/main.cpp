#include "Engine.h"

using namespace SanDX;


//_tMain?
//첫번째 파라미터는 창을 관리하는 곳의 포인터
//두번째 파라미터는 이제 쓰지 않는 파라미터
//하위 호환성을 위해 유지중
//세번째는 창모드 켤 때 옵션값
//사실상 첫번째 파라미터를 위해 쓰는 것
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd) 
{
    //wide character는 앞에 L을 붙여야함
    //TEXT는 유니코드가 설정되어있다면 앞에 L을 붙여주는 매크로 없으면 문자열만
    //프로젝트 속성에 유니코드 사용하는지 구성 속성 - 고급에서 확인해야함 
    //const wchar_t className[] = TEXT("Sample Window Class");

    Engine engine(800, 600, TEXT("Engine Demo"), hInstance);
    engine.Run();

    return 0;
}