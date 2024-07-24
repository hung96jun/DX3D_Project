#pragma once

struct BoneDesc
{
	UINT BoneIndex;
	float Padding[3];
};

///////////////////////////////////////////////////////////////////////////////
class ModelBone
{
public:
	ModelBone();
	~ModelBone();

	const int& GetIndex() { return Index; }

	const int& GetParentIndex() { return ParentIndex; }
	ModelBone* GetParent() { return Parent; }

	wstring GetName() { return Name; }

	Matrix& GetTransform() { return Transform; }
	void SetTransform(Matrix& Mat) { Transform = Mat; }

public:
	int Index;
	wstring Name;

	int ParentIndex;
	ModelBone* Parent = nullptr;

	Matrix Transform;
	vector<ModelBone*> Childs;
};
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ModelMeshPart
{
public:
	ModelMeshPart();
	~ModelMeshPart();

	void SetMaterial(wstring MatrialFile) { MaterialName = MatrialFile; }

	void SetStartVertex(const UINT StartVertex) { this->StartVertex = StartVertex; }
	void SetVertexCount(const UINT VertexCount) { this->VertexCount = VertexCount; }
	void SetStartIndex(const UINT StartIndex) { this->StartIndex = StartIndex; }
	void SetIndexCount(const UINT IndexCount) { this->IndexCount = IndexCount; }

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
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ModelMesh
{
public:
	ModelMesh();
	~ModelMesh();

	void SetTag(const string Tag) { this->Tag = Tag; }

	void SetVertexCount(const UINT VertexCount) { this->VertexCount = VertexCount; }
	void SetIndexCount(const UINT IndexCount) { this->IndexCount = IndexCount; }

	void SetVertices(const vector<VertexModel>& Vertices) { this->Vertices = Vertices; }
	void SetIndices(const vector<UINT>& Indices) { this->Indices = Indices; }

	void SetBone(ModelBone* Bone) { this->Bone = Bone; }

	const int GetBoneIndex() { return BoneIndex; }

	void Update();
	void Render();
	void Render(UINT DrawCount);

	void Binding();

	void SetShader(wstring ShaderFile);

	void SetBoneIndex(const int Index) { BoneIndex = Index; }
	const int GetBondIndex() { return BoneIndex; }
	ModelBone* GetBone() { return Bone; }
	
	Transformation& GetTransform() { return Transform; }
	void SetTransform(Transformation& Transform) { this->Transform = Transform; }

	void AddMeshPart(ModelMeshPart* Part) { MeshParts.push_back(Part); }

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
///////////////////////////////////////////////////////////////////////////////