#include "Engine.h"

using namespace SanDX;


//_tMain?
//ù��° �Ķ���ʹ� â�� �����ϴ� ���� ������
//�ι�° �Ķ���ʹ� ���� ���� �ʴ� �Ķ����
//���� ȣȯ���� ���� ������
//����°�� â��� �� �� �ɼǰ�
//��ǻ� ù��° �Ķ���͸� ���� ���� ��
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd) 
{
    //wide character�� �տ� L�� �ٿ�����
    //TEXT�� �����ڵ尡 �����Ǿ��ִٸ� �տ� L�� �ٿ��ִ� ��ũ�� ������ ���ڿ���
    //������Ʈ �Ӽ��� �����ڵ� ����ϴ��� ���� �Ӽ� - ��޿��� Ȯ���ؾ��� 
    //const wchar_t className[] = TEXT("Sample Window Class");

    Engine engine(800, 600, TEXT("Engine Demo"), hInstance);
    engine.Run();

    return 0;
}