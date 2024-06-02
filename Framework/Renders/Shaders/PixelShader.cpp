#include "PixelShader.h"

PixelShader::PixelShader(wstring File)
	:Shader(File)
{
	CONSTRUCTOR_DEBUG();

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	HRESULT result;
	result = D3DCompileFromFile(File.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0", flags, 0, &Blob, nullptr);

	result = D3D::GetDevice()->CreatePixelShader(Blob->GetBufferPointer(),
		Blob->GetBufferSize(), nullptr, &PShader);
	CHECK(result);
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
