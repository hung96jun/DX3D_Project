#include "Libraries.h"
#include "Framework.h"
#include "ModelMesh.h"

///////////////////////////////////////////////////////////////////////////////
// Model Bone
///////////////////////////////////////////////////////////////////////////////
ModelBone::ModelBone()
{
	CONSTRUCTOR_DEBUG();
}

ModelBone::~ModelBone()
{
	DESTRUCTOR_DEBUG();
}

void ModelBone::Update()
{
	//if (Parent == nullptr)
	//{
	//	Transform.Update();
	//	return;
	//}

	//Vector3 pos, rot, scale;
	//pos = Parent->Transform.GetPosition();
	//rot = Parent->Transform.GetRotation();
	//scale = Vector3(1.0f);

	//Matrix posM, rotM, scaleM;
	//posM = XMMatrixTranslation(pos.X, pos.Y, pos.Z);
	//rotM = XMMatrixRotationRollPitchYaw(rot.X, rot.Y, rot.Z);
	//scaleM = XMMatrixScaling(scale.X, scale.Y, scale.Z);
	//XMMATRIX parentMatrix = scaleM * rotM * posM;
	//Transform.Update(parentMatrix);

	Transform.Update();
}
///////////////////////////////////////////////////////////////////////////////
// ModelMeshPart
///////////////////////////////////////////////////////////////////////////////
ModelMeshPart::ModelMeshPart()
{
	CONSTRUCTOR_DEBUG();

	Mat = new Material();
}

ModelMeshPart::~ModelMeshPart()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(Mat);
}

void ModelMeshPart::Update()
{
}

void ModelMeshPart::Render()
{
	Mat->Set();

	D3D::GetDC()->DrawIndexed(IndexCount, StartIndex, 0);
}

void ModelMeshPart::Render(UINT DrawCount)
{
	Mat->Set();
	D3D::GetDC()->DrawIndexedInstanced(IndexCount, DrawCount, StartIndex, 0, 0U);
}

//void ModelMeshPart::Binding()
//{
//	/**
//	* Model �����͸� �Ű������� �޾ƿͼ� ���� Model�� �ѱ�� ����� ����ϴµ� �̷� ��� Model Ŭ������
//	* friendȭ ���Ѿ� �ؼ� �ϴ��� ����.
//	* ���� �����ϰ� �ִ� ���
//	* 1. Material�� ���ε��ϴ� �۾��̹Ƿ� ���� �Ҵ�� Material ������ ��ȯ���� Model ���ο��� ���ε� �ϴ� �۾�
//	* 2. ���� Model���� �ش� Ŭ������ �������� �ʴ� ��� ���� ������ friend�� ��Ű���� �ʰ� �����ؼ� �۾�
//	*		2���� ��� ���ɼ��� ����
//	*/
//}

void ModelMeshPart::SetMaterials(vector<Material*> Materials)
{
	Material* srcMaterial = nullptr;
	for (Material* mat : Materials)
	{
		if (mat->GetTag() == ToString(MaterialName))
			srcMaterial = mat;
	}

	if (srcMaterial == nullptr) return;

	Mat = new Material();
	Mat->SetAmbient(srcMaterial->GetAmbient());
	Mat->SetDiffuse(srcMaterial->GetDiffuse());
	Mat->SetSpecular(srcMaterial->GetSpecular());
	Mat->SetEmissive(srcMaterial->GetEmissive());

	if (srcMaterial->GetDiffuseMap() != nullptr)
		Mat->SetDiffuseMap(srcMaterial->GetDiffuseMap());

	if (srcMaterial->GetSpecularMap() != nullptr)
		Mat->SetSpecularMap(srcMaterial->GetSpecularMap());

	if (srcMaterial->GetNormalMap() != nullptr)
		Mat->SetNormalMap(srcMaterial->GetNormalMap());
}

void ModelMeshPart::SetShader(wstring ShaderFile)
{
	Mat->SetShader(ShaderFile);
}
///////////////////////////////////////////////////////////////////////////////
// ModelMesh
///////////////////////////////////////////////////////////////////////////////
ModelMesh::ModelMesh()
{
	CONSTRUCTOR_DEBUG();

	WBuffer = new MatrixBuffer();
	//BoneBuffer = new ConstBuffer(&BoneInfo, sizeof(BoneDesc));
}

ModelMesh::~ModelMesh()
{
	DESTRUCTOR_DEBUG();
	////SAFE_DELETE(PerFrame);

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);

	//SAFE_DELETE(BoneBuffer);
	SAFE_DELETE(WBuffer);

	//SAFE_DELETE(Bone);

	//for (ModelMeshPart* part : MeshParts)
	//	SAFE_DELETE(part);
}

void ModelMesh::Update()
{
	//// �̰� ����
	//BoneInfo.BoneIndex = BoneIndex;

	//// PerFrame->Update();

	//for (ModelMeshPart* part : MeshParts)
	//	part->Update();

	Bone->Update();
}

void ModelMesh::Render()
{
	// �ش� �κ� ���ε� �����̶� ���� �ѹ� Ȯ��
	//BoneBuffer->SetVS();

	//PerFrame->Render();

	VBuffer->Set();
	IBuffer->Set();

	WBuffer->Set(Bone->Transform.GetWorld());
	WBuffer->SetVS(0);

	VShader->Set();

	for (ModelMeshPart* part : MeshParts)
		part->Render();
}

void ModelMesh::Render(UINT DrawCount)
{
	//// �ش� �κ� ���ε� �����̶� ���� �ѹ� Ȯ��
	////BoneBuffer->SetVS();

	////PerFrame->Render();

	//VBuffer->Set();
	//IBuffer->Set();

	//VShader->Set();

	//for (ModelMeshPart* part : MeshParts)
	//	part->Render(DrawCount);
}

//void ModelMesh::Binding()
//{
//	VBuffer = new VertexBuffer(Vertices.data(), static_cast<UINT>(Vertices.size()), sizeof(VertexModel));
//	IBuffer = new IndexBuffer(Indices.data(), static_cast<UINT>(Indices.size()));
//
//	/**
//	* �ش� �κ� ��� ó������ ��� �غ�����
//	*/
//	//for (ModelMeshPart* part : MeshParts)
//	//	part->Binding(model);
//}

void ModelMesh::SetMaterials(vector<Material*>& Materials)
{
	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexModel), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), static_cast<UINT>(Indices.size()));

	for (ModelMeshPart* part : MeshParts)
		part->SetMaterials(Materials);
}

void ModelMesh::SetShader(wstring ShaderFile)
{
	//SAFE_DELETE(PerFrame);
	//PerFrame = new PerFrame(ShaderFile);

	//sBoneBuffer = shader->AsConstantBuffer("CB_Bones");

	VShader = ShaderManager::Get()->AddVS(ShaderFile);
	
	for (ModelMeshPart* part : MeshParts)
		part->SetShader(ShaderFile);
}

void ModelMesh::GUIRender()
{
	string Tag;
	Tag = ToString(Bone->Name);

	if (Bone->Transform.GetTag() == "")
		Bone->Transform.SetTag(ToString(Bone->Name));

	Bone->Transform.GUIRender();
}
