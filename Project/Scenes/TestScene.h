#pragma once

class Object;
class Grid;

class Material;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Initialize() override;
	void Disable() override {};
	void Destroy() override;

	void Update() override;

	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

	void UIRender() override {}
	void GUIRender() override;

	void ResizeScreen() override {};

private:
	//Object* TestObject = nullptr;
	//Grid* GridObject = nullptr;

	vector<Vertex> Vertices;
	vector<int> Indices;

	Vector3 Pos, Rot, Scale;

	VertexShader* VShader;
	PixelShader* PShader;
	
	VertexBuffer* VBuffer;
	IndexBuffer* IBuffer;
	//FloatBuffer* FBuffer;
	MatrixBuffer* WBuffer;

	//Texture* DiffuseMap[2];
	//Texture* DiffuseMap;

	//Matrix World;
	Transformation Transform;

	float Color[3] = { 0.5, 0.0, 0.0 };

	vector<Float4> Colors;

	//Material* Mat;

	float Ratio = 1.0f;
};

