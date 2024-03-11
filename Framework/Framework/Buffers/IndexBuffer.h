#pragma once

class IndexBuffer
{
public:
	IndexBuffer(void* Data, UINT Count);
	~IndexBuffer();

	void Set();

private:
	ID3D11Buffer* Buffer;
};