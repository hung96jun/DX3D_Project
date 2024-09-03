#include "ConstBuffer.h"
#include "Systems/D3D.h"
#include "Framework.h"

ConstBuffer::ConstBuffer(void* Data, UINT DataSize)
	:Data(Data), DataSize(DataSize)
{
	CONSTRUCTOR_DEBUG();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = DataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D::GetDevice()->CreateBuffer(&desc, nullptr, &Buffer);
}

ConstBuffer::~ConstBuffer()
{
	DESTRUCTOR_DEBUG();

	SAFE_RELEASE(Buffer);
}

void ConstBuffer::SetVS(UINT Slot)
{
	D3D::GetDC()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResource);
	memcpy(SubResource.pData, Data, DataSize);
	D3D::GetDC()->Unmap(Buffer, 0);

	D3D::GetDC()->VSSetConstantBuffers(Slot, 1, &Buffer);
}

void ConstBuffer::SetPS(UINT Slot)
{
	D3D::GetDC()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResource);
	memcpy(SubResource.pData, Data, DataSize);
	D3D::GetDC()->Unmap(Buffer, 0);

	D3D::GetDC()->PSSetConstantBuffers(Slot, 1, &Buffer);
}

void ConstBuffer::SetCS(UINT Slot)
{
	D3D::GetDC()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResource);
	memcpy(SubResource.pData, Data, DataSize);
	D3D::GetDC()->Unmap(Buffer, 0);

	D3D::GetDC()->CSSetConstantBuffers(Slot, 1, &Buffer);
}
