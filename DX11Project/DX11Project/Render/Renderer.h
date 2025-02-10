#pragma once
#include "../Type.h"
#include <d3d11.h>
#include <dxgi.h>

//������ ����������
//���� ���̴������� ��ȯ�� �Ѵ�
//���� ��ȯ + ���� �ܰ��� ����� ���� �ܰ��� �Է°�

namespace SanDX {
	//�׷���ī�忡�� ó���ϴ� ���� ����
	//RHI - Render Hardware Interface
	class Renderer {
	public:
		Renderer(uint32 width, uint32 helgiht, HWND window);
		~Renderer();

		//TODO: Scene ���� �ѱ��
		void Draw();

	private:
		// @Temp
		//���� ���� (���� ���� ����)
		ID3D11Buffer* vertexBuffer = nullptr;
		//�ε��� ���� (���� ���� �� ���� ���� ����)
		ID3D11Buffer* indexBuffer = nullptr;

		//�Է� ���̾ƿ�
		ID3D11InputLayout* inputLayout = nullptr;

		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11VertexShader* fragmentShader = nullptr;

	private:
		//��ġ��
		ID3D11Device* device = nullptr;
		//���� ��ο� �� ���
		ID3D11DeviceContext* context = nullptr;
		//�� ���� ����(���� ����)
		IDXGISwapChain* swapChain = nullptr;

		//����
		ID3D11RenderTargetView* renderTargetView = nullptr;
		//�� ��Ʈ
		D3D11_VIEWPORT viewport;
	};
}