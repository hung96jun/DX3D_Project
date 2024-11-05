#pragma once

class InstanceScene2 : public Scene
{
public:
	void Initialize() override;
	void Disable() override {}
	void Destroy() override;
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
	VertexBuffer* InstanceBuffer;

	vector<Transformation> Transforms;
	//vector<InstData> Instances;
	vector<Matrix> Instances;

	vector<VertexUV> Vertices;
	vector<UINT> Indices;

	Material* Mat;

	MatrixBuffer* WBuffer;
	
	Transformation Transform;
};

