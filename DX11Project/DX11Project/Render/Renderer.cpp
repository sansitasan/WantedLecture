#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>

#define RESULT(result, message)\
if (FAILED(result))\
{\
	MessageBoxA(nullptr, message, "Error", MB_OK);\
	DebugBreak();\
}\

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

		//���� ü�� ���� ����ü
		//DXGI_MODE_DESC BufferDesc;
		//DXGI_SAMPLE_DESC SampleDesc;
		//DXGI_USAGE BufferUsage;
		//UINT BufferCount;
		//HWND OutputWindow;
		//BOOL Windowed;
		//DXGI_SWAP_EFFECT SwapEffect;
		//UINT Flags;

		//��Ƽ ���ø� ���� ���� Ȯ��
		//�� ���߿�����
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		//â���?
		swapChainDesc.Windowed = true;
		//Ÿ�� â
		swapChainDesc.OutputWindow = window;
		//
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		//����� ����. 1���� ���� ����
		swapChainDesc.BufferCount = 1;
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
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		//�� ���� �� ����, ����� ���� ���� �ʿ��ϴٸ� �̰� ��� ��
		//D3D11CreateDevice
		//�� ���� �� ����
		//ù �Ķ���Ͱ� ����̽� ������ �ִ� �Ķ����
		//�ι�°�� �ϵ���� Ÿ��
		//�׹�°�� ��ġ ������ �ʿ��� �ɼǰ�
		//5�� �迭��, 6�� �迭 ����
		//D3D11_SDK_VERSION�� ����, dx skd�� window�� ���յǸ鼭 ������
		//D3D_featureLevel�� nullptr�� ������ ä�õ� ������ �˷��ִ� ��
		//������ �ʿ����� �ʴ�. ������ ���� �������� �ʴ� ������ ���� �� ������ ifdef�� ������ �뵵
		HRESULT result = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&swapChain,
			&device,
			nullptr,
			&context);

		RESULT(result, "Failed to create devices.");
		//GPU�� CPU�� �޸� ���� ������� ����
		//�޸𸮸� �̸�ŭ �� �״� �� ������ ��Ƶֶ�
		//GPU�� �޸𸮴� void*�� �ִ�
		//�ν��Ͻ��� �ٷ��� �ʴ´� - ���� ��ü�� �� ���� �׸��� ���
		//�޽ð� ���ƾ� �ϰ�, ���̴��� ���ƾ� �Ѵ�
		//�� ���� �������� ������ �¾ƾ� �Ѵ�
		//DX12 or VULKAN�� ���� ������ ����ȭ�� �ؾ� �� �� ����

		//���� Ÿ�� �� ����
		ID3D11Texture2D* backBuffer = nullptr;
		//���� ���� �۾�
		//swapChain->GetBuffer(0, __uuidof(backBuffer), reinterpret_cast<void**>(&backBuffer));
		result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		RESULT(result, "Failed to get Back Buffer.");

		if (!backBuffer) return;
		//1, 2 �Ķ���� �� �� �ϳ��� ��� �־��ָ� �ȴ�
		result = device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
		RESULT(result, "Failed to create render target view.");

		//OM = Output Merger
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		ZeroMemory(&viewport, sizeof(viewport));
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = .5f;
		viewport.MinDepth = -.5f;

		context->RSSetViewports(1, &viewport);

		// @Temp: �ӽ� ���ҽ� ����
		//Buffer = �޸� ���
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		//x, y, z, �� �� ��, ���� ����
		vertexBufferDesc.ByteWidth = sizeof(float) * 3 * 3;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = {};
		
		float vertices[] = {
			0, .5f, .5f,
			.5f, -.5f, .5f,
			-.5f, -.5f, .5f,
		};

		vertexData.pSysMem = vertices;

		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
		RESULT(result, "Failed to create vertex buffer");

		//�ε��� ���� ����
		int indices[] = { 0, 1, 2 };

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(int) * 3;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};

		indexData.pSysMem = indices;

		result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
		RESULT(result, "Failed to create index buffer");

		ID3DBlob* vertexShaderBuffer = nullptr;
		//�ι�°�� ���̴� ��ġ, ����Ʈ �� ���� �������ִ� ��
		//����°�� ��Ŭ��� ���� ��ġ
		//�׹�°�� ���� �Լ� �̸�
		//�ټ���°�� ���� ����
		//id3dblob�� �޾ƿ� ��
		//�������� ���̴� ������ �޾ƿ� �� �ִ� ��
		result = D3DCompileFromFile(
			TEXT("vertex.hlsl"),
			nullptr,
			nullptr,
			"main",
			"vs_5_0",
			0,
			0,
			&vertexShaderBuffer,
			nullptr
		);
		//D3DReadFileToBlob()
		RESULT(result, "Failed to compile vertex shader");

		result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			nullptr,
			&vertexShader);

		RESULT(result, "Failed to create vertex shader");
		
		//ù��°�� hlsl�� �ø�ƽ �̸�
		//�ι�°�� ���° �ø�ƽ����
		//����°�� � ����������
		//�׹�°�� slot
		//�ټ���°�� ������(����Ʈ�� ���) ���⼭ ���ؽ�, uv ���� �������� ����Ѵ�
		//���ؽ��� ó�����ʹϱ� 0, uv�� ���ؽ� ������ ����Ʈ...�̷� ��
		//������°�� �ν��Ͻ��� �� ������
		//�ϰ���°�� �ν��Ͻ��� �ɼ�
		D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		
		//�Է� ���̾ƿ�
		//�Է� ���̾ƿ��� ���÷����� �� �ִ�?
		//
		result = device->CreateInputLayout(inputDesc, _countof(inputDesc),
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			&inputLayout
		);

		RESULT(result, "Failed to create input layout");
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		//�׸��� �� (BeginScene)
		//����� (Clear) = �� �������� ����� ���� memset
		float color[] = { 1, 1, 1, 1 };
		context->ClearRenderTargetView(renderTargetView, color);
		//��ο� (Draw, Render)

		//���� ��ȯ (EndScene, Present)
		//����� ȭ���ֻ��� ���� ����ȭ�� �Ұ���
		//3�� ������ vs 60hz�� �� 1�̸� 60hz��, �ƴϸ� 3�� ����������
		swapChain->Present(1u, 0u);
	}
}