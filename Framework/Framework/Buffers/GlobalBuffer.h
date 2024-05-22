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

class ViewProjectionBuffer : public ConstBuffer
{
private:
	struct BufferData
	{
		Matrix View;
		Matrix InvView;
		Matrix Projection;
	};

public:
	ViewProjectionBuffer() : ConstBuffer(&Data, sizeof(BufferData))
	{
		Data.View = XMMatrixIdentity();
		Data.InvView = XMMatrixIdentity();
		Data.Projection = XMMatrixIdentity();
	}

	void Set(Matrix View, Matrix InvView, Matrix Projection)
	{
		Data.View = XMMatrixTranspose(View);
		Data.InvView = XMMatrixTranspose(InvView);
		Data.Projection = XMMatrixTranspose(Projection);
	}

private:
	BufferData Data;
};

class MaterialBuffer : public ConstBuffer
{
public:
	struct BufferData
	{
		Float4 Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		Float4 Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
		Float4 Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
		Float4 Emissive = { 0.0f, 0.0f, 0.0f, 1.0f };

		float Shininess = 24.0f;
		int HasNormalMap = 0;
		float Padding[2];
	};

public:
	MaterialBuffer() : ConstBuffer(&Data, sizeof(BufferData)) {}
	BufferData& Get() { return Data; }

private:
	BufferData Data;
};

class FloatBuffer : public ConstBuffer
{
public:
	FloatBuffer() : ConstBuffer(&Value, sizeof(FloatBuffer))
	{
		Value = 0.0f;
	}

	void Set(float Value) { this->Value = Value; }

private:
	float Value;
	float Padding[3];
};
