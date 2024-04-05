#pragma once
#include "ConstBuffer.h"

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer() : ConstBuffer(&Mat, sizeof(Matrix))
	{
		Mat = XMMatrixIdentity();
	}

	void Set(Matrix Value)
	{
		Mat = XMMatrixTranspose(Value);
	}

private:
	Matrix Mat;
};

class WorldBuffer : public ConstBuffer
{
private:
	struct BufferData
	{
		Matrix World = XMMatrixIdentity();
		int Type;
		float Padding[3];
	};

public:
	WorldBuffer() : ConstBuffer(&Data, sizeof(BufferData)) {}
	
	void Set(Matrix Value)
	{
		Data.World = XMMatrixTranspose(Value);
	}

	void SetType(int Type)
	{
		Data.Type = Type;
	}

private:
	BufferData Data;
};

class ViewBuffer : public ConstBuffer
{
private:
	struct BufferData
	{
		Matrix View;
		Matrix InvView;
	};

public:
	ViewBuffer() : ConstBuffer(&Data, sizeof(BufferData))
	{
		Data.View = XMMatrixIdentity();
		Data.InvView = XMMatrixIdentity();
	}

	void Set(Matrix View, Matrix InvView)
	{
		Data.View = XMMatrixTranspose(View);
		Data.InvView = XMMatrixTranspose(InvView);
	}

private:
	BufferData Data;
};