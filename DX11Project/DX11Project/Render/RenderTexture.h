#pragma once
#include "Texture.h"
#include "Type.h"
#include <d3d11.h>

namespace SanDX {
	class RenderTexture : public Texture {
	public:
		RenderTexture(uint32 width = 0, uint32 height = 0);
		virtual ~RenderTexture() override;

		FORCEINLINE ID3D11RenderTargetView* GetRenderTarget() const { return renderTargetView; }
		FORCEINLINE ID3D11RenderTargetView** GetRenderTargetAddress() { return &renderTargetView; }

		FORCEINLINE ID3D11DepthStencilView* GetDepthStencilView() const { return depthStencilView; }
		FORCEINLINE ID3D11DepthStencilView** GetDepthStencilViewAddress() { return &depthStencilView; }

	private:
		ID3D11RenderTargetView* renderTargetView = nullptr;
		ID3D11DepthStencilView* depthStencilView = nullptr;
	};
}