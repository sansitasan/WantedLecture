#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>
#include "Math/Vector3.h"
#include "QuadMesh.h"
#include "TriangleMesh.h"

//버텍스는 정점을 받고
//프래그먼트는 픽셀을 받는다
//따라서 같은 결과라면 정점에서 처리하는 편이 효율적일 것이다

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

		//장치 생성
		//첫번째 어댑터에서 모니터 정보도 얻어올 수 있다.
		//nullptr은 기본 어댑터
		//두번째는 드라이버 타입, 이를 소프트웨어로 만들었으면 핸들 값을 세번째에 넘겨준다
		//4, 5, 6, 7은 밑과 동일
		//device다음의 nullptr은 최종 확정된 그래픽 드라이버 버전을 가져오는 부분
		//피쳐 레벨을 넘겨주고 나서 우리가 최종 확정된 버전을 알고 싶을 때 사용
		//D3D_FEATURE_LEVEL을 포인터로 넘기기

		//스왑 체인을 같이 만드느냐, 따로 만드느냐의 차이는
		//장치 만들기 전에 

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

		//IDXGIFactory 리소스 생성
		IDXGIFactory* factory = nullptr;

		//__uuidof는 uuid를 가져온다.이 값은 IDXGIFactory 상단 매크로에 적힌 string
		//MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
		result =  CreateDXGIFactory(__uuidof(factory), reinterpret_cast<void**>(&factory));
		//CreateDXGIFactory(IID_PPV_ARGS(&factory)); 위와 동일 매크로

		RESULT(result, TEXT("Failed to Create dxgiFactory"));

		//멀티 샘플링 지원 여부 확인
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		//창모드
		swapChainDesc.Windowed = true;
		//타겟 창
		swapChainDesc.OutputWindow = window;
		//
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		//백버퍼 개수. 1개면 더블 버퍼
		swapChainDesc.BufferCount = 2;
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
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		result = factory->CreateSwapChain(device, &swapChainDesc, &swapChain);

		RESULT(result, TEXT("Failed to Create SwapChain"));

		//할 일이 더 있음, 모니터 정보 등이 필요하다면 이걸 써야 함
		//D3D11CreateDevice
		//할 일이 좀 적음
		//첫 파라미터가 디바이스 정보를 주는 파라미터
		//두번째는 하드웨어 타입
		//세번재는 소프트웨어 래스터라이저가 있다면 포인터를 넘겨주면 된다. 자신있으면 넣자
		//네번째는 장치 생성에 필요한 옵션값
		//5는 배열값, 6은 배열 개수
		//배열에 있는 값은 DX버젼, 높은 버젼을 위에 둬서 사용할 수 있는 버젼 중 가장 높은 것을 가져오는 것이 바람직할 듯
		//D3D11_SDK_VERSION는 고정, dx sdk가 window와 통합되면서 고정됨
		//D3D_featureLevel이 nullptr인 이유는 채택된 버젼을 알려주는 것
		//지금은 필요하지 않다. 버젼에 따라 지원하지 않는 버젼이 있을 수 있으니 ifdef로 나누는 용도
		//이 정보를 토대로 바인딩
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
		

		//GPU가 CPU의 메모리 공간 생김새를 본다
		//메모리를 이만큼 쓸 테니 이 공간을 잡아둬라
		//GPU의 메모리는 void*로 있다
		//인스턴싱은 다루지 않는다 - 여러 물체를 한 번에 그리는 기술
		//메시가 같아야 하고, 쉐이더가 같아야 한다
		//둘 사이 스레드의 시점이 맞아야 한다
		//DX12 or VULKAN을 가서 스레드 동기화를 해야 알 수 있음

		//렌더 타겟 뷰 생성
		//메모리 공간을 두고 소통하는 창구로 쓰임
		//뷰에 객체 하나의 크기, 총 개수 등을 넣고 GPU에게 보내면 GPU가 VRAM에 공간을 잡는다.
		//CPU도 똑같이 공간을 잡는다.
		ID3D11Texture2D* backBuffer = nullptr;
		//둘은 같은 작업
		//swapChain->GetBuffer(0, __uuidof(backBuffer), reinterpret_cast<void**>(&backBuffer));
		result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		RESULT(result, TEXT("Failed to get Back Buffer."));

		if (!backBuffer) return;
		//1, 2 파라미터 둘 중 하나만 골라서 넣어주면 된다
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

		//렌더 콜을 하면 지우기 때문에 렌더 타겟을 사용하겠다고 명시해줘야 한다.
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);
		//그리기 전 (BeginScene)
		//지우기 (Clear) = 한 색상으로 덮어쓰기 유사 memset
		float color[] = { 1, 1, 1, 1 };
		context->ClearRenderTargetView(renderTargetView, color);

		mesh->Update(1.f / 60.f);
		mesh2->Update(1.f / 60.f);

		//드로우 (Draw, Render)
		mesh->Draw();
		mesh2->Draw();

		//버퍼 교환 (EndScene, Present)
		//모니터 화면주사율 렌더 동기화를 할건지
		//3만 프레임 vs 60hz일 때 1이면 60hz로, 아니면 3만 프레임으로
		swapChain->Present(1u, 0u);
	}
}