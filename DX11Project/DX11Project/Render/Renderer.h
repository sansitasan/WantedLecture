#pragma once
#include "../Type.h"
#include <d3d11.h>
#include <dxgi.h>
#include <memory>

#include "Core.h"

//렌더링 파이프라인
//정점 쉐이더에서는 변환을 한다
//공간 변환 + 이전 단계의 출력은 다음 단계의 입력값

namespace SanDX {
	//그래픽카드에서 처리하는 일을 관리
	//RHI - Render Hardware Interface
	class Renderer {
		friend class Engine;

	public:
		Renderer(uint32 width, uint32 helgiht, HWND window);
		~Renderer();

		void Draw(std::shared_ptr<class Scene> scene);

		void OnResize(uint32 width, uint32 height);

	private:
		void EmptyRTVsAndSRVs();

	private:

		bool isResizing = false;
		//장치류
		ID3D11Device* device = nullptr;
		//실제 드로우 콜 담당
		ID3D11DeviceContext* context = nullptr;
		//백 버퍼 관리(이중 버퍼)
		IDXGISwapChain* swapChain = nullptr;

		//버퍼
		ID3D11RenderTargetView* renderTargetView = nullptr;
		//depth도 24비트를 사용하는 이유
		//8비트만 사용해도 괜찮지만 세분화해서 저장하면 좋기 때문이다
		//그래서 뎁스만 저장하지 않고 스텐실도 저장한다
		//총 depth 24 + 스텐실 8 해서 픽셀 하나당 32비트를 사용한다
		//스텐실은 0, 1만 저장한다
		ID3D11DepthStencilView* depthStencilView = nullptr;
		//뷰 포트
		D3D11_VIEWPORT viewport;
	};
}