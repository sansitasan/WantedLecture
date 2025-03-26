#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>
#include "Math/Vector3.h"
#include "QuadMesh.h"
#include "TriangleMesh.h"

//���ؽ��� ������ �ް�
//�����׸�Ʈ�� �ȼ��� �޴´�
//���� ���� ������ �������� ó���ϴ� ���� ȿ������ ���̴�

namespace SanDX {
	Renderer::Renderer(uint32 width, uint32 height, HWND window)
		: viewport()
	{
		uint32 flag = 0x20;
#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		//�� ó������ �����ϴ� ���̷�Ʈ ������ Ȯ����
		//�տ������� üũ�ؼ� ���� ���� �����ϴ� ��ȣ�� ������
		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		//��ġ ����
		//ù��° ����Ϳ��� ����� ������ ���� �� �ִ�.
		//nullptr�� �⺻ �����
		//�ι�°�� ����̹� Ÿ��, �̸� ����Ʈ����� ��������� �ڵ� ���� ����°�� �Ѱ��ش�
		//4, 5, 6, 7�� �ذ� ����
		//device������ nullptr�� ���� Ȯ���� �׷��� ����̹� ������ �������� �κ�
		//���� ������ �Ѱ��ְ� ���� �츮�� ���� Ȯ���� ������ �˰� ���� �� ���
		//D3D_FEATURE_LEVEL�� �����ͷ� �ѱ��

		//���� ü���� ���� �������, ���� ��������� ���̴�
		//��ġ ����� ���� 

		HRESULT result = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			nullptr,
			&context
		);

		RESULT(result, TEXT("Failed to Create Device"));

		//IDXGIFactory ���ҽ� ����
		IDXGIFactory* factory = nullptr;

		//__uuidof�� uuid�� �����´�.�� ���� IDXGIFactory ��� ��ũ�ο� ���� string
		//MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
		result =  CreateDXGIFactory(__uuidof(factory), reinterpret_cast<void**>(&factory));
		//CreateDXGIFactory(IID_PPV_ARGS(&factory)); ���� ���� ��ũ��

		RESULT(result, TEXT("Failed to Create dxgiFactory"));

		//��Ƽ ���ø� ���� ���� Ȯ��
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		//â���
		swapChainDesc.Windowed = true;
		//Ÿ�� â
		swapChainDesc.OutputWindow = window;
		//
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		//����� ����. 1���� ���� ����
		swapChainDesc.BufferCount = 2;
		//��Ƽ ���ø� ����, ����(���� count - 1 ��) 1�� �� ���ٴ� �� ������ �ϳ��ϱ�
		//��Ƽ�ٸ���� - ������ �ȼ� ������
		//������ �����
		//������ �������ϸ� �ϵ����� �������ֳ� ���۵�� ���� ������
		//����Ƽ�� �ϵ��� �� ����
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		//unorm - unsigned normalize(0~1)
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//ȭ��ó�� �� ��(����Ʈ <> �����) ��� ó���� ������
		//������ ȭ��ó���ϸ� �ܻ��� ���� ���(�ϵ���� ����)�� �־ SEQUENTIAL�� ����
		//�� ���� ��ü�Ұ��� �ε巴�� �ִϸ��̼��� �� ����
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		result = factory->CreateSwapChain(device, &swapChainDesc, &swapChain);

		RESULT(result, TEXT("Failed to Create SwapChain"));

		//�� ���� �� ����, ����� ���� ���� �ʿ��ϴٸ� �̰� ��� ��
		//D3D11CreateDevice
		//�� ���� �� ����
		//ù �Ķ���Ͱ� ����̽� ������ �ִ� �Ķ����
		//�ι�°�� �ϵ���� Ÿ��
		//������� ����Ʈ���� �����Ͷ������� �ִٸ� �����͸� �Ѱ��ָ� �ȴ�. �ڽ������� ����
		//�׹�°�� ��ġ ������ �ʿ��� �ɼǰ�
		//5�� �迭��, 6�� �迭 ����
		//�迭�� �ִ� ���� DX����, ���� ������ ���� �ּ� ����� �� �ִ� ���� �� ���� ���� ���� �������� ���� �ٶ����� ��
		//D3D11_SDK_VERSION�� ����, dx sdk�� window�� ���յǸ鼭 ������
		//D3D_featureLevel�� nullptr�� ������ ä�õ� ������ �˷��ִ� ��
		//������ �ʿ����� �ʴ�. ������ ���� �������� �ʴ� ������ ���� �� ������ ifdef�� ������ �뵵
		//�� ������ ���� ���ε�
		//result = D3D11CreateDeviceAndSwapChain(
		//	nullptr,
		//	D3D_DRIVER_TYPE_HARDWARE,
		//	nullptr,
		//	flag,
		//	featureLevels,
		//	_countof(featureLevels),
		//	D3D11_SDK_VERSION,
		//	&swapChainDesc,
		//	&swapChain,
		//	&device,
		//	nullptr,
		//	&context);
		//
		//RESULT(result, TEXT("Failed to create devices."));
		

		//GPU�� CPU�� �޸� ���� ������� ����
		//�޸𸮸� �̸�ŭ �� �״� �� ������ ��Ƶֶ�
		//GPU�� �޸𸮴� void*�� �ִ�
		//�ν��Ͻ��� �ٷ��� �ʴ´� - ���� ��ü�� �� ���� �׸��� ���
		//�޽ð� ���ƾ� �ϰ�, ���̴��� ���ƾ� �Ѵ�
		//�� ���� �������� ������ �¾ƾ� �Ѵ�
		//DX12 or VULKAN�� ���� ������ ����ȭ�� �ؾ� �� �� ����

		//���� Ÿ�� �� ����
		//�޸� ������ �ΰ� �����ϴ� â���� ����
		//�信 ��ü �ϳ��� ũ��, �� ���� ���� �ְ� GPU���� ������ GPU�� VRAM�� ������ ��´�.
		//CPU�� �Ȱ��� ������ ��´�.
		ID3D11Texture2D* backBuffer = nullptr;
		//���� ���� �۾�
		//swapChain->GetBuffer(0, __uuidof(backBuffer), reinterpret_cast<void**>(&backBuffer));
		result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		RESULT(result, TEXT("Failed to get Back Buffer."));

		if (!backBuffer) return;
		//1, 2 �Ķ���� �� �� �ϳ��� ��� �־��ָ� �ȴ�
		result = device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
		RESULT(result, TEXT("Failed to create render target view."));

		//OM = Output Merger
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.f;
		viewport.MinDepth = .0f;

		context->RSSetViewports(1, &viewport);
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		if (mesh == nullptr) {
			mesh = std::make_unique<QuadMesh>();
			mesh->transform.scale = Vector3::One * 0.5f;
			mesh->transform.position.x = 0.5f;
		}

		if (mesh2 == nullptr) {
			mesh2 = std::make_unique<QuadMesh>();
			mesh2->transform.scale = Vector3::One * 0.5f;
			mesh2->transform.position.x = -0.5f;
		}

		//���� ���� �ϸ� ����� ������ ���� Ÿ���� ����ϰڴٰ� �������� �Ѵ�.
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);
		//�׸��� �� (BeginScene)
		//����� (Clear) = �� �������� ����� ���� memset
		float color[] = { 1, 1, 1, 1 };
		context->ClearRenderTargetView(renderTargetView, color);

		mesh->Update(1.f / 60.f);
		mesh2->Update(1.f / 60.f);

		//��ο� (Draw, Render)
		mesh->Draw();
		mesh2->Draw();

		//���� ��ȯ (EndScene, Present)
		//����� ȭ���ֻ��� ���� ����ȭ�� �Ұ���
		//3�� ������ vs 60hz�� �� 1�̸� 60hz��, �ƴϸ� 3�� ����������
		swapChain->Present(1u, 0u);
	}
}