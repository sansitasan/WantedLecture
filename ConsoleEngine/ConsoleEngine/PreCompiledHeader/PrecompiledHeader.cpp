#include "PrecompiledHeader.h"

//목적은 빌드 속도 향상
//헤더를 하나 정해서 컴파일을 미리 해둔다
//이를 include하면 컴파일 된 것을 가져다 쓴다, 복사해서 쓰는 게 아님
//이는 프로젝트 설정에서 하는 것
//자주 바뀌지 않을 내용만을 써야 빌드 속도가 늘어난다. 그래야지 여기가 재컴파일이 잘 안 될 테니까
//https://learn.microsoft.com/ko-kr/cpp/build/creating-precompiled-header-files?view=msvc-170