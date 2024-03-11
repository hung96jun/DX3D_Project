#include "Libraries.h"
#include "IndexBuffer.h"
#include "Systems/D3D.h"

IndexBuffer::IndexBuffer(void* Data, UINT Count)
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * Count;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = Data;

	D3D::GetDevice()->CreateBuffer(&desc, &data, &Buffer);
}

IndexBuffer::~IndexBuffer()
{
	Buffer->Release();
}

void IndexBuffer::Set()
{
	D3D::GetDC()->IASetIndexBuffer(Buffer, DXGI_FORMAT_R32_UINT, 0);
}
