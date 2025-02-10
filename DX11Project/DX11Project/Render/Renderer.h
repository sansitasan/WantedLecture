#pragma once
#include "../Type.h"
#include <d3d11.h>
#include <dxgi.h>

//렌더링 파이프라인
//정점 쉐이더에서는 변환을 한다
//공간 변환 + 이전 단계의 출력은 다음 단계의 입력값

namespace SanDX {
	//그래픽카드에서 처리하는 일을 관리
	//RHI - Render Hardware Interface
	class Renderer {
	public:
		Renderer(uint32 width, uint32 helgiht, HWND window);
		~Renderer();

		//TODO: Scene 정보 넘기기
		void Draw();

	private:
		// @Temp
		//정점 버퍼 (정점 정보 전달)
		ID3D11Buffer* vertexBuffer = nullptr;
		//인덱스 버퍼 (정점 조립 시 정점 순서 전달)
		ID3D11Buffer* indexBuffer = nullptr;

		//입력 레이아웃
		ID3D11InputLayout* inputLayout = nullptr;

		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11VertexShader* fragmentShader = nullptr;

	private:
		//장치류
		ID3D11Device* device = nullptr;
		//실제 드로우 콜 담당
		ID3D11DeviceContext* context = nullptr;
		//백 버퍼 관리(이중 버퍼)
		IDXGISwapChain* swapChain = nullptr;

		//버퍼
		ID3D11RenderTargetView* renderTargetView = nullptr;
		//뷰 포트
		D3D11_VIEWPORT viewport;
	};
}