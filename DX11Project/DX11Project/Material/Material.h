#pragma once

#include <string>
#include <d3d11.h>
#include "Core.h"

namespace SanDX {
	class RHI {
	public:
		virtual void Bind() = 0;
	};

	class Material {
	public:
		Material(const std::wstring& name = L"Default");
		virtual ~Material();

		//GPU�� ���̴� ��ü�� ����(���ε�)�ϴ� �Լ�
		virtual void Bind();
	protected:
		//���̴� �̸�
		std::wstring name;

		ID3D11InputLayout* inputLayout = nullptr;

		ID3D11VertexShader* vertexShader = nullptr;
		ID3DBlob* vertexShaderBuffer = nullptr;

		ID3D11PixelShader* fragmentShader = nullptr;
		ID3DBlob* fragmentShaderBuffer = nullptr;
	};

}