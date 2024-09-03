#include "Framework.h"
#include "VertexBuffer.h"
#include "Systems/D3D.h"

VertexBuffer::VertexBuffer(void* Data, UINT Stride, UINT Count, bool bCPUWrite, bool bGPUWrite)
	:Stride(Stride), bCPUWrite(bCPUWrite), bGPUWrite(bGPUWrite)
{
	CONSTRUCTOR_DEBUG();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = Stride * Count;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	if (bCPUWrite == false && bGPUWrite == false)
	{
		desc.Usage = D3D11_USAGE_IMMUTABLE;
	}
	else if (bCPUWrite == true && bGPUWrite == false)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else if (bCPUWrite == false && bGPUWrite == true)
	{
		desc.Usage = D3D11_USAGE_DEFAULT;
	}
	else
	{
		desc.Usage = D3D11_USAGE_STAGING;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		desc.BindFlags = 0;		// usage가 staging일 경우 BindFlas는 0
	}

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = Data;

	HRESULT result = D3D::GetDevice()->CreateBuffer(&desc, &data, &Buffer);
	CHECK(result);
}

VertexBuffer::~VertexBuffer()
{
	DESTRUCTOR_DEBUG();

	SAFE_RELEASE(Buffer);
}

void VertexBuffer::Set(UINT Slot, D3D11_PRIMITIVE_TOPOLOGY Type)
{
	D3D::GetDC()->IASetVertexBuffers(Slot, 1, &Buffer, &Stride, &Offset);
	D3D::GetDC()->IASetPrimitiveTopology(Type);
}

void VertexBuffer::Update(void* Data, UINT Count)
{
	D3D::GetDC()->UpdateSubresource(Buffer, 0, nullptr, Data, Stride, Count);
}
