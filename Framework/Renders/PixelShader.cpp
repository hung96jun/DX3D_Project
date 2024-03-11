#include "Libraries.h"
#include "Framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring File)
{
	this->File = File;
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	D3DCompileFromFile(File.c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0",
		flags, 0, &Blob, nullptr);

	D3D::GetDevice()->CreatePixelShader(Blob->GetBufferPointer(),
		Blob->GetBufferSize(), nullptr, &PS);
}

PixelShader::~PixelShader()
{
	PS->Release();
}

void PixelShader::Set()
{
	D3D::GetDC()->PSSetShader(PS, nullptr, 0);
}
