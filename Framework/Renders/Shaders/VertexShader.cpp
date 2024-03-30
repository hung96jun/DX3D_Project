#include "VertexShader.h"

VertexShader::VertexShader(wstring File)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	D3DCompileFromFile(File.c_str(), nullptr, nullptr,
		"VS", "vs_5_0", flags, 0, &Blob, nullptr);

	D3D::GetDevice()->CreateVertexShader(Blob->GetBufferPointer(),
		Blob->GetBufferSize(), nullptr, &VShader);

	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT size = ARRAYSIZE(desc);
	D3D::GetDevice()->CreateInputLayout(desc, size, 
		Blob->GetBufferPointer(), Blob->GetBufferSize(), 
		&InputLayout);
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(VShader);
	SAFE_RELEASE(InputLayout);
}

void VertexShader::Set()
{
	D3D::GetDC()->IASetInputLayout(InputLayout);
	D3D::GetDC()->VSSetShader(VShader, nullptr, 0);
}
