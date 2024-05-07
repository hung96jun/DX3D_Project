#include "Framework.h"
#include "IndexBuffer.h"
#include "Systems/D3D.h"

IndexBuffer::IndexBuffer(void* Data, UINT Count)
{
	CONSTRUCTOR_DEBUG();

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * Count;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = Data;

	D3D::GetDevice()->CreateBuffer(&desc, &data, &Buffer);
}

IndexBuffer::~IndexBuffer()
{
	DESTRUCTOR_DEBUG();

	SAFE_RELEASE(Buffer);
}

void IndexBuffer::Set()
{
	D3D::GetDC()->IASetIndexBuffer(Buffer, DXGI_FORMAT_R32_UINT, 0);
}

void IndexBuffer::Update(void* Data, UINT Count)
{
	D3D::GetDC()->UpdateSubresource(Buffer, 0, nullptr, Data, sizeof(UINT), Count);
}
