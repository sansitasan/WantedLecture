#pragma once
#include "Engine.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include <iostream>

using namespace SanDX;


//_tMain?
//ù��° �Ķ���ʹ� â�� �����ϴ� ���� ������
//�ι�° �Ķ���ʹ� ���� ���� �ʴ� �Ķ����
//���� ȣȯ���� ���� ������
//����°�� â��� �� �� �ɼǰ�
//��ǻ� ù��° �Ķ���͸� ���� ���� ��
//int WINAPI WinMain(
//    _In_ HINSTANCE hInstance,
//    _In_opt_ HINSTANCE hPrevInstance,
//    _In_ LPSTR lpCmdLine,
//    _In_ int nShowCmd) 
//{
//    //wide character�� �տ� L�� �ٿ�����
//    //TEXT�� �����ڵ尡 �����Ǿ��ִٸ� �տ� L�� �ٿ��ִ� ��ũ�� ������ ���ڿ���
//    //������Ʈ �Ӽ��� �����ڵ� ����ϴ��� ���� �Ӽ� - ��޿��� Ȯ���ؾ��� 
//    //const wchar_t className[] = TEXT("Sample Window Class");
//
//    Engine engine(800, 600, TEXT("Engine Demo"), hInstance);
//    engine.Run();
//
//    return 0;
//}


int WINAPI main() {
	Engine engine(800, 600, TEXT("Engine Demo"), GetModuleHandle(nullptr));
	engine.Run();

	//Vector2 a = Vector2(3, 4);
	//Vector2 b = Vector2(2, 9);
	//Vector2 x = a * 3.f;
}