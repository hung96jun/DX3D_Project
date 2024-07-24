#include "Libraries.h"
#include "Framework.h"
#include "ModelMesh.h"


ModelBone::ModelBone()
{
	CONSTRUCTOR_DEBUG();
}

ModelBone::~ModelBone()
{
	DESTRUCTOR_DEBUG();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ModelMeshPart::ModelMeshPart()
{
	CONSTRUCTOR_DEBUG();
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

void ModelMeshPart::Binding()
{
	/**
	* Model 포인터를 매개변수로 받아와서 값을 Model에 넘기는 방식을 사용하는데 이럴 경우 Model 클래스를
	* friend화 시켜야 해서 일단은 보류.
	* 현재 생각하고 있는 방법
	* 1. Material을 바인딩하는 작업이므로 값이 할당된 Material 정보를 반환시켜 Model 내부에서 바인드 하는 작업
	* 2. 만일 Model에서 해당 클래스를 참조하지 않는 경우 기존 방법대로 friend를 시키지는 않고 참조해서 작업
	*		2번의 경우 가능성은 낮음
	*/
}

void ModelMeshPart::SetShader(wstring ShaderFile)
{
	Mat->SetShader(ShaderFile);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ModelMesh::ModelMesh()
{
	CONSTRUCTOR_DEBUG();

	BoneBuffer = new ConstBuffer(&BoneInfo, sizeof(BoneDesc));
}

ModelMesh::~ModelMesh()
{
	DESTRUCTOR_DEBUG();
	//SAFE_DELETE(PerFrame);
	
	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);

	SAFE_DELETE(BoneBuffer);

	for (ModelMeshPart* part : MeshParts)
		SAFE_DELETE(part);
}

void ModelMesh::Update()
{
	BoneInfo.BoneIndex = BoneIndex;

	// PerFrame->Update();

	for (ModelMeshPart* part : MeshParts)
		part->Update();

	Transform.Update();
}

void ModelMesh::Render()
{
	// 해당 부분 바인드 시점이랑 슬롯 넘버 확인
	//BoneBuffer->SetVS();

	//PerFrame->Render();

	VBuffer->Set();
	IBuffer->Set();

	for (ModelMeshPart* part : MeshParts)
		part->Render();
}

void ModelMesh::Render(UINT DrawCount)
{
	// 해당 부분 바인드 시점이랑 슬롯 넘버 확인
	//BoneBuffer->SetVS();
	
	//PerFrame->Render();

	VBuffer->Set();
	IBuffer->Set();

	for (ModelMeshPart* part : MeshParts)
		part->Render(DrawCount);
}

void ModelMesh::Binding()
{
	VBuffer = new VertexBuffer(Vertices.data(), Vertices.size(), sizeof(VertexModel));
	IBuffer = new IndexBuffer(Indices.data(), Indices.size());

	/**
	* 해당 부분 어떻게 처리할지 고민 해봐야함
	*/
	//for (ModelMeshPart* part : MeshParts)
	//	part->Binding(model);
}

void ModelMesh::SetShader(wstring ShaderFile)
{
	//SAFE_DELETE(PerFrame);
	//PerFrame = new PerFrame(ShaderFile);

	//sBoneBuffer = shader->AsConstantBuffer("CB_Bones");

	for (ModelMeshPart* part : MeshParts)
		part->SetShader(ShaderFile);
}
