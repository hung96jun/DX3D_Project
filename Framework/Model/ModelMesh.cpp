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
	* Model �����͸� �Ű������� �޾ƿͼ� ���� Model�� �ѱ�� ����� ����ϴµ� �̷� ��� Model Ŭ������
	* friendȭ ���Ѿ� �ؼ� �ϴ��� ����.
	* ���� �����ϰ� �ִ� ���
	* 1. Material�� ���ε��ϴ� �۾��̹Ƿ� ���� �Ҵ�� Material ������ ��ȯ���� Model ���ο��� ���ε� �ϴ� �۾�
	* 2. ���� Model���� �ش� Ŭ������ �������� �ʴ� ��� ���� ������ friend�� ��Ű���� �ʰ� �����ؼ� �۾�
	*		2���� ��� ���ɼ��� ����
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
	// �ش� �κ� ���ε� �����̶� ���� �ѹ� Ȯ��
	//BoneBuffer->SetVS();

	//PerFrame->Render();

	VBuffer->Set();
	IBuffer->Set();

	for (ModelMeshPart* part : MeshParts)
		part->Render();
}

void ModelMesh::Render(UINT DrawCount)
{
	// �ش� �κ� ���ε� �����̶� ���� �ѹ� Ȯ��
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
	* �ش� �κ� ��� ó������ ��� �غ�����
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
