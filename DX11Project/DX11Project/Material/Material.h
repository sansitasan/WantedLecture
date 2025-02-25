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

		//GPU에 쉐이더 객체를 연결(바인딩)하는 함수
		virtual void Bind();
	protected:
		//쉐이더 이름
		std::wstring name;

		ID3D11InputLayout* inputLayout = nullptr;

		ID3D11VertexShader* vertexShader = nullptr;
		ID3DBlob* vertexShaderBuffer = nullptr;

		ID3D11PixelShader* fragmentShader = nullptr;
		ID3DBlob* fragmentShaderBuffer = nullptr;
	};

}