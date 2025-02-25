#pragma once
#include "Type.h"
#include <string>
#include <d3d11.h>
#include <memory>
#include "Core.h"

namespace SanDX {
	struct TextureData {
		TextureData() = default;
		~TextureData() {
			free(data);
			data = nullptr;
			if (shaderResourceView) {
				shaderResourceView->Release();
				shaderResourceView = nullptr;
			}

			if (samplerState) {
				samplerState->Release();
				samplerState = nullptr;
			}
		}
		//원시 데이터
		//너비 높이는 GPU가 필요로 함
		//이를 통해 바이트 너비가 필요함
		int32 width = 0;
		int32 height = 0;
		int32 channelCount = 0;
		//픽셀 데이터 1차원 배열(채널의 개수에 따라 타입이 달라지니 타입을 모름)
		//vector2, vector3, vector4 ...
		void* data = nullptr;

		//DX 리소스
		//텍스처 = ShaderResourceView 이거로 만들어야 바인딩이 가능함
		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		//내 UV에 맞는 픽셀 값 줘 = 샘플링
		ID3D11SamplerState* samplerState = nullptr;
	};

	class Texture {
		enum class EBindType {
			VertexShader,
			FragmentShader,
			GeometryShader,
			HullShader,
			DomainShader
		};

	public:
		Texture() = default;
		Texture(const std::string& name, EBindType bindType = EBindType::FragmentShader, uint32 index = 0u);
		virtual ~Texture();

		void Bind();
	protected:
		void LoadTexture(const std::string& name);
		std::string name;
		EBindType bindType;
		uint32 index = 0u;
		std::unique_ptr<TextureData> textureData;
	private:
	};
}