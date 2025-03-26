#pragma once
#include "../Type.h"
#include <d3d11.h>
#include <dxgi.h>
#include <memory>

#include "Core.h"

//������ ����������
//���� ���̴������� ��ȯ�� �Ѵ�
//���� ��ȯ + ���� �ܰ��� ����� ���� �ܰ��� �Է°�

namespace SanDX {
	//�׷���ī�忡�� ó���ϴ� ���� ����
	//RHI - Render Hardware Interface
	class Renderer {
		friend class Engine;

	public:
		Renderer(uint32 width, uint32 helgiht, HWND window);
		~Renderer();

		//TODO: Scene ���� �ѱ��
		void Draw();

	private:
		std::unique_ptr<class QuadMesh> mesh;
		std::unique_ptr<class QuadMesh> mesh2;

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