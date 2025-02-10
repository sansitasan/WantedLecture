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
		//맨 처음부터 지원하는 다이렉트 버젼을 확인함
		//앞에서부터 체크해서 가장 먼저 지원하는 번호를 가져옴
		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		//스왑 체인 정보 구조체
		//DXGI_MODE_DESC BufferDesc;
		//DXGI_SAMPLE_DESC SampleDesc;
		//DXGI_USAGE BufferUsage;
		//UINT BufferCount;
		//HWND OutputWindow;
		//BOOL Windowed;
		//DXGI_SWAP_EFFECT SwapEffect;
		//UINT Flags;

		//멀티 샘플링 지원 여부 확인
		//은 나중에ㅋㅋ
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		//창모드?
		swapChainDesc.Windowed = true;
		//타겟 창
		swapChainDesc.OutputWindow = window;
		//
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		//백버퍼 개수. 1개면 더블 버퍼
		swapChainDesc.BufferCount = 1;
		//멀티 샘플링 개수, 수준(보통 count - 1 값) 1은 안 쓴다는 것 샘플이 하나니까
		//안티앨리어싱 - 보통은 픽셀 뭉개기
		//단점은 흐려짐
		//포워드 렌더링하면 하드웨어에서 지원해주나 디퍼드는 지원 안해줌
		//퀄리티도 하드웨어가 더 좋다
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		//unorm - unsigned normalize(0~1)
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//화면처리 할 때(프론트 <> 백버퍼) 어떻게 처리할 것인지
		//예전에 화면처리하면 잔상이 남는 경우(하드웨어 문제)가 있어서 SEQUENTIAL이 있음
		//한 번에 교체할건지 부드럽게 애니메이션을 줄 건지
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		//할 일이 더 있음, 모니터 정보 등이 필요하다면 이걸 써야 함
		//D3D11CreateDevice
		//할 일이 좀 적음
		//첫 파라미터가 디바이스 정보를 주는 파라미터
		//두번째는 하드웨어 타입
		//네번째는 장치 생성에 필요한 옵션값
		//5는 배열값, 6은 배열 개수
		//D3D11_SDK_VERSION는 고정, dx skd가 window와 통합되면서 고정됨
		//D3D_featureLevel이 nullptr인 이유는 채택된 버젼을 알려주는 것
		//지금은 필요하지 않다. 버젼에 따라 지원하지 않는 버젼이 있을 수 있으니 ifdef로 나누는 용도
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
		//GPU가 CPU의 메모리 공간 생김새를 본다
		//메모리를 이만큼 쓸 테니 이 공간을 잡아둬라
		//GPU의 메모리는 void*로 있다
		//인스턴싱은 다루지 않는다 - 여러 물체를 한 번에 그리는 기술
		//메시가 같아야 하고, 쉐이더가 같아야 한다
		//둘 사이 스레드의 시점이 맞아야 한다
		//DX12 or VULKAN을 가서 스레드 동기화를 해야 알 수 있음

		//렌더 타겟 뷰 생성
		ID3D11Texture2D* backBuffer = nullptr;
		//둘은 같은 작업
		//swapChain->GetBuffer(0, __uuidof(backBuffer), reinterpret_cast<void**>(&backBuffer));
		result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		RESULT(result, "Failed to get Back Buffer.");

		if (!backBuffer) return;
		//1, 2 파라미터 둘 중 하나만 골라서 넣어주면 된다
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

		// @Temp: 임시 리소스 생성
		//Buffer = 메모리 덩어리
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		//x, y, z, 세 개 즉, 정점 세개
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

		//인덱스 버퍼 생성
		int indices[] = { 0, 1, 2 };

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(int) * 3;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};

		indexData.pSysMem = indices;

		result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
		RESULT(result, "Failed to create index buffer");

		ID3DBlob* vertexShaderBuffer = nullptr;
		//두번째는 쉐이더 수치, 라이트 맵 등을 지정해주는 값
		//세번째는 인클루드 파일 위치
		//네번째는 시작 함수 이름
		//다섯번째는 버전 정보
		//id3dblob는 받아올 값
		//마지막은 쉐이더 오류를 받아올 수 있는 것
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
		
		//첫번째는 hlsl의 시멘틱 이름
		//두번째는 몇번째 시멘틱인지
		//세번째는 어떤 데이터인지
		//네번째는 slot
		//다섯번째는 오프셋(바이트로 계산) 여기서 버텍스, uv 등의 오프셋을 계산한다
		//버텍스는 처음부터니까 0, uv는 버텍스 이후의 바이트...이런 식
		//여섯번째는 인스턴스로 할 것인지
		//일곱번째는 인스턴스의 옵션
		D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		
		//입력 레이아웃
		//입력 레이아웃을 리플렉션할 수 있다?
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
		//그리기 전 (BeginScene)
		//지우기 (Clear) = 한 색상으로 덮어쓰기 유사 memset
		float color[] = { 1, 1, 1, 1 };
		context->ClearRenderTargetView(renderTargetView, color);
		//드로우 (Draw, Render)

		//버퍼 교환 (EndScene, Present)
		//모니터 화면주사율 렌더 동기화를 할건지
		//3만 프레임 vs 60hz일 때 1이면 60hz로, 아니면 3만 프레임으로
		swapChain->Present(1u, 0u);
	}
}