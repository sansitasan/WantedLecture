#include "Material.h"
#include <d3dcompiler.h>
#include "../Engine.h"

namespace SanDX {
	Material::Material(const std::wstring& name)
		: name(name) 
	{
		wchar_t path[256] = {};
		swprintf_s(path, 256, L"../CompiledShader/%sVertexShader.cso", name.c_str());
		//두번째는 쉐이더 수치, 라이트 맵 등을 지정해주는 값
		//세번째는 인클루드 파일 위치
		//네번째는 시작 함수 이름
		//다섯번째는 버전 정보
		//id3dblob는 받아올 값
		//마지막은 쉐이더 오류를 받아올 수 있는 것
		//쉐이더 컴파일은 런타임 말고 컴파일 타임에 해두자 좀 - CSO로 만들어지고 이게 obj(컴파일된 파일)과 같다고 보면 됨
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

		//첫번째는 hlsl의 시멘틱 이름
		//두번째는 몇번째 시멘틱인지
		//세번째는 어떤 데이터인지
		//네번째는 slot - 어디부터 어디까지 무슨 데이터고, 이런 식으로 나누는 기준
		//다섯번째는 오프셋(바이트로 계산) 여기서 버텍스, uv 등의 오프셋을 계산한다
		//버텍스는 처음부터니까 0, uv는 버텍스 이후의 바이트...이런 식
		//여섯번째는 인스턴스로 할 것인지
		//일곱번째는 인스턴스의 옵션
		D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		//입력 레이아웃
		//입력 레이아웃을 리플렉션할 수 있다?
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

		//입력 레이아웃 전달
		context.IASetInputLayout(inputLayout);
		//조립 모양 설정
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//쉐이더 설정
		context.VSSetShader(vertexShader, nullptr, 0);
		context.PSSetShader(fragmentShader, nullptr, 0);
	}
}