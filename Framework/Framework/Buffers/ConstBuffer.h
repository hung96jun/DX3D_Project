#pragma once
#include "Libraries.h"

class ConstBuffer
{
public:
	ConstBuffer(void* Data, UINT DataSize);
	virtual ~ConstBuffer();

	void SetVS(UINT Slot);
	void SetPS(UINT Slot);
	void SetCS(UINT Slot);

private:
	ID3D11Buffer* Buffer;

	void* Data;
	UINT DataSize;

	D3D11_MAPPED_SUBRESOURCE SubResource;
};

