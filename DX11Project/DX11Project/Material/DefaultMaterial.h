#pragma once

#include "Material.h"

namespace SanDX {
	class DefaultMaterial : public Material {
	public:
		DefaultMaterial();
		virtual ~DefaultMaterial();

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