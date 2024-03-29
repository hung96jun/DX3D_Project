#include "Libraries.h"
#include "VertexBuffer.h"
#include "Systems/D3D.h"

VertexBuffer::VertexBuffer(void* Data, UINT Stride, UINT Count)
	:Stride(Stride)
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = Stride * Count;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = Data;

	D3D::GetDevice()->CreateBuffer(&desc, &data, &Buffer);
}

VertexBuffer::~VertexBuffer()
{
	Buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY Type)
{
	D3D::GetDC()->IASetVertexBuffers(0, 1, &Buffer, &Stride, &Offset);
	D3D::GetDC()->IASetPrimitiveTopology(Type);
}

void VertexBuffer::Update(void* Data, UINT Count)
{
	D3D::GetDC()->UpdateSubresource(Buffer, 0, nullptr, Data, Stride, Count);
}
