#pragma once

class VertexBuffer
{
public:
	VertexBuffer() = delete;
	VertexBuffer(void* Data, UINT Stride, UINT Count, bool bCPUWrite = false, bool bGPUWrite = true);
	~VertexBuffer();

	void Set(UINT Slot = 0, D3D11_PRIMITIVE_TOPOLOGY Type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void Update(void* Data, UINT Count);

private:
	ID3D11Buffer* Buffer = nullptr;;

	UINT Stride = 0;
	UINT Offset = 0;

	bool bCPUWrite;
	bool bGPUWrite;
};

