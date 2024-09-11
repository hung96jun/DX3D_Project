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
//	* Model 포인터를 매개변수로 받아와서 값을 Model에 넘기는 방식을 사용하는데 이럴 경우 Model 클래스를
//	* friend화 시켜야 해서 일단은 보류.
//	* 현재 생각하고 있는 방법
//	* 1. Material을 바인딩하는 작업이므로 값이 할당된 Material 정보를 반환시켜 Model 내부에서 바인드 하는 작업
//	* 2. 만일 Model에서 해당 클래스를 참조하지 않는 경우 기존 방법대로 friend를 시키지는 않고 참조해서 작업
//	*		2번의 경우 가능성은 낮음
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
	//// 이건 뭐지
	//BoneInfo.BoneIndex = BoneIndex;

	//// PerFrame->Update();

	//for (ModelMeshPart* part : MeshParts)
	//	part->Update();

	Bone->Update();
}

void ModelMesh::Render()
{
	// 해당 부분 바인드 시점이랑 슬롯 넘버 확인
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
	//// 해당 부분 바인드 시점이랑 슬롯 넘버 확인
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
//	* 해당 부분 어떻게 처리할지 고민 해봐야함
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
