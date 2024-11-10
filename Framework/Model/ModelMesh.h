#pragma once

/**
* 분할시켜서 작업
* ModelMesh와 ModelMeshPart를 조합해서 먼저 Material없이 Vertex로만 렌더 테스트
* (아마 ModelBone도 같이 작업을 해야할것 같긴함)
* 후에 Material 추가하는 방향으로
*/

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

public:
	void Update();
	void GUIRender();

	void BoneRender();

public:
	int Index = -1;
	wstring Name = L"";

	int ParentIndex = -1;
	ModelBone* Parent = nullptr;

	Transformation Transform;
	vector<ModelBone*> Childs;
};
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ModelMeshPart
{
public:
	ModelMeshPart();
	~ModelMeshPart();

public:
	void SetMaterial(wstring MatrialFile) { MaterialName = MatrialFile; }

	void SetStartVertex(const UINT StartVertex) { this->StartVertex = StartVertex; }
	void SetVertexCount(const UINT VertexCount) { this->VertexCount = VertexCount; }
	void SetStartIndex(const UINT StartIndex) { this->StartIndex = StartIndex; }
	void SetIndexCount(const UINT IndexCount) { this->IndexCount = IndexCount; }

	void Update();
	//void Set();
	void Render();
	void Render(UINT DrawCount);

	//void Binding();
	void SetMaterials(vector<Material*>& Materials);
	void SetShader(wstring ShaderFile);

private:
	Material* Mat = nullptr;
	wstring MaterialName = L"";

	UINT StartVertex = 0;
	UINT VertexCount = 0;

	UINT StartIndex = 0;
	UINT IndexCount = 0;
};
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ModelMesh
{
public:
	ModelMesh();
	~ModelMesh();

public:
	void Update();
	void Render();
	void Render(UINT DrawCount);
	void GUIRender();

	void SetVertexCount(const UINT VertexCount) { this->VertexCount = VertexCount; }
	void SetIndexCount(const UINT IndexCount) { this->IndexCount = IndexCount; }

	//void SetVertices(const vector<VertexModel>& Vertices) { this->Vertices = Vertices; }
	void SetVertices(const vector<VertexModel>& Vertices) { this->Vertices = Vertices; }
	void SetIndices(const vector<UINT>& Indices) { this->Indices = Indices; }

	void SetBone(ModelBone* Bone) { this->Bone = Bone; }

	const int GetBoneIndex() { return BoneIndex; }

	void Binding();
	void SetMaterials(vector<Material*>& Materials);

	void SetShader(wstring ShaderFile);

	void SetBoneIndex(const int Index) { BoneIndex = Index; }
	const int GetBondIndex() { return BoneIndex; }
	ModelBone* GetBone() { return Bone; }

	void AddMeshPart(ModelMeshPart* Part) { MeshParts.push_back(Part); }

private:
	VertexShader* VShader = nullptr;
	//PixelShader* PShader = nullptr;

	//PerFrame

	int BoneIndex;
	// Root Bone
	ModelBone* Bone = nullptr;
	BoneDesc BoneInfo;

	VertexBuffer* VBuffer = nullptr;
	UINT VertexCount;
	vector<VertexModel> Vertices;

	IndexBuffer* IBuffer = nullptr;
	UINT IndexCount;
	vector<UINT> Indices;

	MatrixBuffer* WBuffer = nullptr;
	ConstBuffer* BoneBuffer = nullptr;

	vector<ModelMeshPart*> MeshParts;
};
///////////////////////////////////////////////////////////////////////////////
