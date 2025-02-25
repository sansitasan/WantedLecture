#include "Texture.h"
#include "Engine.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stbi_image.h"

namespace SanDX {
	Texture::Texture(const std::string& name, EBindType bindType, uint32 index)
		:name(name), bindType(bindType), index(index)
	{
		LoadTexture(name);
	}

	Texture::~Texture()
	{

	}

	void Texture::Bind()
	{
		if (!textureData) return;

		static ID3D11DeviceContext& context = Engine::Get().Context();

		switch (bindType) {
			case EBindType::VertexShader:
				context.VSSetShaderResources(index, 1, &textureData->shaderResourceView);
				context.VSSetSamplers(index, 1, &textureData->samplerState);
				break;

			case EBindType::FragmentShader:
				context.PSSetShaderResources(index, 1, &textureData->shaderResourceView);
				context.PSSetSamplers(index, 1, &textureData->samplerState);
				break;
		}
	}

	void Texture::LoadTexture(const std::string& name)
	{
		char path[256] = {};
		sprintf_s(path, 256, "../Assets/Textures/%s", name.c_str());
		textureData = std::make_unique<TextureData>();

		textureData->data = stbi_load(
			path, 
			&textureData->width, 
			&textureData->height, 
			&textureData->channelCount, 
			0);

		if (!textureData->data) {
			std::cout << "Error: Failed to load texutre file!\n " << name << '\n';
			__debugbreak();
		}

		//리소스 생성
		static ID3D11Device& device = Engine::Get().Device();

		//이미지 기반으로 데이터 생성
		ID3D11Texture2D* texture = nullptr;
		D3D11_TEXTURE2D_DESC textureDesc = {};
		D3D11_SUBRESOURCE_DATA data = {};

		data.pSysMem = textureData->data;
		data.SysMemPitch = textureData->width * textureData->channelCount;

		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//텍스쳐 수
		//큐브맵같은 건 6개를 쓰기도 하니까 6
		textureDesc.ArraySize = 1;
		textureDesc.MipLevels = 1;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.Width = textureData->width;
		textureDesc.Height = textureData->height;

		HRESULT result = device.CreateTexture2D(&textureDesc, &data, &texture);
		RESULT(result, "Error: Failed to create texture2d.\n");

		//지금 방법은 리소스 제작에 초기값을 제작하는 방법
		//초기값 없이 제작할 때 필요한 방법이 Desc
		result = device.CreateShaderResourceView(texture, nullptr, &textureData->shaderResourceView);
		RESULT(result, "Error: Failed to create ShaderResourceView.\n");

		if (texture) {
			texture->Release();
			texture = nullptr;
		}

		//샘플링
		D3D11_SAMPLER_DESC samplerDesc = {};

		//point, linear, anisotropic 방식
		//앞 둘은 알고 맨 뒤는 사다리꼴 느낌으로 필터링을 한다
		//왜 이렇게 하면 더 잘 나오는 걸까?
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		//0 미만, 1 초과에 대해서 어떻게 대응하는지
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		//얘도 원근감이 있나?
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.MinLOD = -FLT_MAX;
		//고려 픽셀 최대치
		samplerDesc.MaxAnisotropy = 3;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

		result = device.CreateSamplerState(&samplerDesc, &textureData->samplerState);
		RESULT(result, "Error: Failed to create ShaderResourceView.\n");
	}
}