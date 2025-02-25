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
		//���� ������
		//�ʺ� ���̴� GPU�� �ʿ�� ��
		//�̸� ���� ����Ʈ �ʺ� �ʿ���
		int32 width = 0;
		int32 height = 0;
		int32 channelCount = 0;
		//�ȼ� ������ 1���� �迭(ä���� ������ ���� Ÿ���� �޶����� Ÿ���� ��)
		//vector2, vector3, vector4 ...
		void* data = nullptr;

		//DX ���ҽ�
		//�ؽ�ó = ShaderResourceView �̰ŷ� ������ ���ε��� ������
		ID3D11ShaderResourceView* shaderResourceView = nullptr;
		//�� UV�� �´� �ȼ� �� �� = ���ø�
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