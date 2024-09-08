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
		Mat->SetSpecularMap(srcMaterial->GetDiffuseMap());

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
	Transform.SetScale(Vector3(0.01f));
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

	Transform.Update();
}

void ModelMesh::Render()
{
	// �ش� �κ� ���ε� �����̶� ���� �ѹ� Ȯ��
	//BoneBuffer->SetVS();

	//PerFrame->Render();

	VBuffer->Set();
	IBuffer->Set();

	WBuffer->Set(Transform.GetWorld());
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

void ModelMesh::GUIRender(string Tag)
{
	if (ImGui::TreeNode(Tag.c_str()))
	{
		float pos[3];
		float scale[3];
		float rot[3];

		pos[0] = Transform.GetPosition().X;
		pos[1] = Transform.GetPosition().Y;
		pos[2] = Transform.GetPosition().Z;
		ImGui::DragFloat3((Tag + "_Position").c_str(), pos, 0.01f);
		Transform.SetPosition(Vector3(pos[0], pos[1], pos[2]));

		scale[0] = Transform.GetScale().X;
		scale[1] = Transform.GetScale().Y;
		scale[2] = Transform.GetScale().Z;
		ImGui::DragFloat3((Tag + "_Scale").c_str(), scale, 0.01f);
		Transform.SetScale(Vector3(scale[0], scale[1], scale[2]));

		rot[0] = Transform.GetRotation().X;
		rot[1] = Transform.GetRotation().Y;
		rot[2] = Transform.GetRotation().Z;
		ImGui::DragFloat3((Tag + "_Rotation").c_str(), rot, 0.01f);
		Transform.SetRotation(Vector3(rot[0], rot[1], rot[2]));

		ImGui::TreePop();
	}
}
