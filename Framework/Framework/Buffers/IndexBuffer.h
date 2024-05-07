#pragma once

class IndexBuffer
{
public:
	IndexBuffer() = delete;
	IndexBuffer(void* Data, UINT Count);
	~IndexBuffer();

	void Set();

	void Update(void* Data, UINT Count);

private:
	ID3D11Buffer* Buffer;
};

