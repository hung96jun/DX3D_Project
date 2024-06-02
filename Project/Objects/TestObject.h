#pragma once

class TestObject
{
public:
	TestObject(const int Index);
	~TestObject();

	void Update();
	void Render();
	void GUIRender();

private:
	vector<VertexUV> Vertices;
	vector<int> Indices;

	Transformation Transform;

	VertexBuffer* VBuffer;
	IndexBuffer* IBuffer;
	MatrixBuffer* WBuffer;

	Material* Mat;

	Vector3 Pos, Scale, Rot;

	int Index = 0;
};

