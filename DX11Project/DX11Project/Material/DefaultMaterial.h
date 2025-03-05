#pragma once

#include "Material.h"

namespace SanDX {
	class DefaultMaterial : public Material {
	public:
		DefaultMaterial();
		virtual ~DefaultMaterial();

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