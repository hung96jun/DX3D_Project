#pragma once
#include "Libraries.h"

template<size_t T>
class Matrix
{
public:
	Matrix() {}
	~Matrix() {}

	static void* operator new(size_t size)
	{
		return _aligned_malloc(size, T);
	}

	static void* operator delete(void* memory)
	{
		return _aligned_free(memory);
	}

	XMMATRIX Get() { return Value; }

private:
	XMMATRIX Value;
};