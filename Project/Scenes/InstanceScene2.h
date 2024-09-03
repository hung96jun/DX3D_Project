#pragma once

struct InstData
{
	Float4 Vec1;
	Float4 Vec2;
	Float4 Vec3;
	Float4 Vec4;
};

class InstanceScene2 : public Scene
{
public:
	void Initialize() override;
	void Disable() override {}
	void Destory() override;
	void Update() override;
	void PreRender() override {}
	void Render() override;
	void PostRender() override {}
	void UIRender() override {}
	void GUIRender() override;
	void ResizeScreen() override {}

private:
	void CreateMesh(const Vector3 Size);

private:
	const UINT Count = 10;

	VertexShader* VShader;
	PixelShader* PShader;

	VertexBuffer* VBuffer;
	IndexBuffer* IBuffer;

	vector<VertexUV> Vertices;
	vector<UINT> Indices;

	Material* Mat;

	MatrixBuffer* WBuffer;

	VertexBuffer* InstanceBuffer;
	vector<Transformation> Transforms;
	vector<InstData> Instances;

	Transformation Transform;
};

