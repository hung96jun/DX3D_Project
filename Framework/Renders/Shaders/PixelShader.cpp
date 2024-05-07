#include "PixelShader.h"

PixelShader::PixelShader(wstring File)
	:Shader(File)
{
	CONSTRUCTOR_DEBUG();

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	D3DCompileFromFile(File.c_str(), nullptr, nullptr,
		"PS", "ps_5_0", flags, 0, &Blob, nullptr);

	D3D::GetDevice()->CreatePixelShader(Blob->GetBufferPointer(),
		Blob->GetBufferSize(), nullptr, &PShader);
}

PixelShader::~PixelShader()
{
	DESTRUCTOR_DEBUG();

	SAFE_RELEASE(PShader);
}

void PixelShader::Set()
{
	D3D::GetDC()->PSSetShader(PShader, nullptr, 0);
}
