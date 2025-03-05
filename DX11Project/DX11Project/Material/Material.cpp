#include "Material.h"
#include <d3dcompiler.h>
#include "../Engine.h"

namespace SanDX {
	Material::Material(const std::wstring& name)
		: name(name) 
	{
		wchar_t path[256] = {};
		swprintf_s(path, 256, L"../CompiledShader/%sVertexShader.cso", name.c_str());
		//�ι�°�� ���̴� ��ġ, ����Ʈ �� ���� �������ִ� ��
		//����°�� ��Ŭ��� ���� ��ġ
		//�׹�°�� ���� �Լ� �̸�
		//�ټ���°�� ���� ����
		//id3dblob�� �޾ƿ� ��
		//�������� ���̴� ������ �޾ƿ� �� �ִ� ��
		//���̴� �������� ��Ÿ�� ���� ������ Ÿ�ӿ� �ص��� �� - CSO�� ��������� �̰� obj(�����ϵ� ����)�� ���ٰ� ���� ��
		//HRESULT result = D3DCompileFromFile(
		//	path,
		//	nullptr,
		//	nullptr,
		//	"main",
		//	"vs_5_0",
		//	0,
		//	0,
		//	&vertexShaderBuffer,
		//	nullptr
		//);
		////D3DReadFileToBlob()
		//RESULT(result, "Failed to compile vertex shader");

		ID3D11Device& device = Engine::Get().Device();

		HRESULT result = D3DReadFileToBlob(path, &vertexShaderBuffer);

		RESULT(result, TEXT("Failed to read vertex shader object file"));

		result = device.CreateVertexShader(
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			nullptr,
			&vertexShader);

		RESULT(result, TEXT("Failed to create vertex shader"));

		//ù��°�� hlsl�� �ø�ƽ �̸�
		//�ι�°�� ���° �ø�ƽ����
		//����°�� � ����������
		//�׹�°�� slot - ������ ������ ���� �����Ͱ�, �̷� ������ ������ ����
		//�ټ���°�� ������(����Ʈ�� ���) ���⼭ ���ؽ�, uv ���� �������� ����Ѵ�
		//���ؽ��� ó�����ʹϱ� 0, uv�� ���ؽ� ������ ����Ʈ...�̷� ��
		//������°�� �ν��Ͻ��� �� ������
		//�ϰ���°�� �ν��Ͻ��� �ɼ�
		D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		//�Է� ���̾ƿ�
		//�Է� ���̾ƿ��� ���÷����� �� �ִ�?
		result = device.CreateInputLayout(
			inputDesc, 
			_countof(inputDesc),
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			&inputLayout
		);

		RESULT(result, TEXT("Failed to create input layout"));

		//swprintf_s(path, 256, L"HLSLShader/%sFragmentShader.hlsl", name.c_str());
		//
		//result = D3DCompileFromFile(
		//	path,
		//	nullptr,
		//	nullptr,
		//	"main",
		//	"ps_5_0",
		//	0,
		//	0,
		//	&fragmentShaderBuffer,
		//	nullptr
		//);
		//
		//RESULT(result, "Failed to compile fragment shader");
		swprintf_s(path, 256, L"../CompiledShader/%sFragmentShader.cso", name.c_str());
		result = D3DReadFileToBlob(path, &fragmentShaderBuffer);

		RESULT(result, TEXT("Failed to read fragment shader object file"));

		result = device.CreatePixelShader(
			fragmentShaderBuffer->GetBufferPointer(),
			fragmentShaderBuffer->GetBufferSize(),
			nullptr,
			&fragmentShader);

		RESULT(result, TEXT("Failed to create fragment shader"));
	}

	Material::~Material()
	{
		if (inputLayout) inputLayout->Release();
		inputLayout = nullptr;

		if (vertexShader) vertexShader->Release();
		vertexShader = nullptr;

		if (vertexShaderBuffer) vertexShaderBuffer->Release();
		vertexShaderBuffer = nullptr;

		if (fragmentShader) fragmentShader->Release();
		fragmentShader = nullptr;

		if (fragmentShaderBuffer) fragmentShaderBuffer->Release();
		fragmentShaderBuffer = nullptr;
	}

	void Material::Bind()
	{
		static ID3D11DeviceContext& context = Engine::Get().Context();

		//�Է� ���̾ƿ� ����
		context.IASetInputLayout(inputLayout);
		//���� ��� ����
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//���̴� ����
		context.VSSetShader(vertexShader, nullptr, 0);
		context.PSSetShader(fragmentShader, nullptr, 0);
	}
}