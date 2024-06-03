#pragma once

class BoxShape;

class TestObject
{
public:
	TestObject(const int Index);
	~TestObject();

	void Update();
	void Render();
	void GUIRender();

private:
	Transformation Transform;

	MatrixBuffer* WBuffer;

	BoxShape* Mesh;
	Material* Mat;

	Vector3 Pos, Scale, Rot;

	int Index = 0;
};

