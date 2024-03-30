#pragma once

class Object
{
public:
	Object() = delete;
	Object(const Vector2 Pos, const Vector2 Size);
	virtual ~Object();

	virtual void Update();
	virtual void Render();

private:
	VertexShader* VShader = nullptr;
	PixelShader* PShader = nullptr;
	VertexBuffer* VBuffer = nullptr;
	IndexBuffer* IBuffer = nullptr;

	vector<VertexColor> Vertices;
	vector<UINT> Indices;
};
