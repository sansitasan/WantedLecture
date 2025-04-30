#include "RenderTexture.h"
#include "Engine.h"
#include "Core.h"

namespace SanDX {
	RenderTexture::RenderTexture(uint32 width, uint32 height)
	{
		static ID3D11Device& device = Engine::Get().Device();

		width ? width : Engine::Get().Width();
		height ? height : Engine::Get().Height();

		textureData = std::make_unique<TextureData>();
		textureData->width = width;
		textureData->height = height;

		ID3D11Texture2D* renderTargetResource = nullptr;
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.ArraySize = 1;
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

		RESULT
		(
			device.CreateTexture2D(&textureDesc, nullptr, &renderTargetResource),
			TEXT("Failed to Create Render Texture 2D")
		);

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};
		renderTargetViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		RESULT(
			device.CreateRenderTargetView(renderTargetResource, &renderTargetViewDesc, &renderTargetView),
			TEXT("Failed to create render target view for render texture")
		);

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		RESULT(
			device.CreateShaderResourceView(renderTargetResource, &shaderResourceViewDesc, &textureData->shaderResourceView),
			TEXT("Failed to create shader resource view for render texture")
		);

		renderTargetResource->Release();
		renderTargetResource = nullptr;

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.MinLOD = -FLT_MAX;
		samplerDesc.MaxAnisotropy = 3;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		
		RESULT(
			device.CreateSamplerState(&samplerDesc, &textureData->samplerState),
			TEXT("Failed to create sampler state for render texture")
		);

		ID3D11Texture2D* depthStencilBuffer = nullptr;
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		RESULT(device.CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer),
			TEXT("Failed to create depth stencil buffer"));

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = depthStencilDesc.Format;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		RESULT(device.CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView),
			TEXT("Failed to create depth stencil buffer"));

		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;
	}

	RenderTexture::~RenderTexture()
	{
		if (renderTargetView) {
			renderTargetView->Release();
			renderTargetView = nullptr;
		}

		if (depthStencilView) {
			depthStencilView->Release();
			depthStencilView = nullptr;
		}
	}
}