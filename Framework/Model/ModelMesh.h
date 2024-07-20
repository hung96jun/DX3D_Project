#pragma once

struct BoneDesc
{
	UINT BoneIndex;
	float Padding[3];
};

class ModelBone
{
public:
	ModelBone() {}
	~ModelBone() {}

	const int& GetIndex() { return Index; }

	const int& GetParentIndex() { return ParentIndex; }
	ModelBone* GetParent() { return Parent; }

	wstring GetName() { return Name; }

	Matrix& GetTransform() { return Transform; }
	void SetTransform(Matrix& M) { Transform = M; }

public:
	int Index;
	wstring Name;

	int ParentIndex;
	ModelBone* Parent = nullptr;

	Matrix Transform;
	vector<ModelBone*> Childs;
};

class ModelMeshPart
{
public:
	ModelMeshPart() = default;
	~ModelMeshPart();

	void Update();
	void Render();
	void Render(UINT DrawCount);

	void Binding();
	void SetShader(wstring ShaderFile);

private:
	Material* Mat = nullptr;
	wstring MaterialName;

	UINT StartVertex;
	UINT VertexCount;

	UINT StartIndex;
	UINT IndexCount;
};

class ModelMesh
{
public:
	ModelMesh();
	~ModelMesh();

	void Update();
	void Render();
	void Render(UINT DrawCount);

	void Binding();

	void SetShader(wstring ShaderFile);

	const int GetBondIndex() { return BoneIndex; }
	ModelBone* GetBone() { return Bone; }
	
	Transformation& GetTransform() { return Transform; }
	void SetTransform(Transformation& Transform) { this->Transform = Transform; }

private:
	//VertexShader* VShader = nullptr;
	//PixelShader* PShader = nullptr;

	Transformation Transform;
	//PerFrame

	int BoneIndex;
	ModelBone* Bone;
	BoneDesc BoneInfo;

	VertexBuffer* VBuffer;
	UINT VertexCount;
	vector<VertexModel> Vertices;

	IndexBuffer* IBuffer;
	UINT IndexCount;
	vector<UINT> Indices;

	ConstBuffer* BoneBuffer;

	vector<ModelMeshPart*> MeshParts;
};