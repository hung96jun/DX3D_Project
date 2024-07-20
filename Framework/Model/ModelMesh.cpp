#include "Libraries.h"
#include "Framework.h"
#include "ModelMesh.h"

///////////////////////////////////////////////////////////////////////////////

ModelMeshPart::~ModelMeshPart()
{
	SAFE_DELETE(Mat);
}

void ModelMeshPart::Update()
{
}

void ModelMeshPart::Render()
{
	Mat->Set();

	D3D::GetDC()->DrawIndexed(IndexCount, 0, 0);
}

void ModelMeshPart::Render(UINT DrawCount)
{
	Mat->Set();

	D3D::GetDC()->DrawIndexedInstanced(IndexCount, DrawCount, 0, 0, 0);
}

void ModelMeshPart::Binding()
{
	// �ϴ� ����
}

void ModelMeshPart::SetShader(wstring ShaderFile)
{
	Mat->SetShader(ShaderFile);
}
///////////////////////////////////////////////////////////////////////////////

ModelMesh::ModelMesh()
{
	BoneBuffer = new ConstBuffer(&BoneInfo, sizeof(BoneDesc));
}

ModelMesh::~ModelMesh()
{
	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);

	SAFE_DELETE(BoneBuffer);

	for (ModelMeshPart* part : MeshParts)
		SAFE_DELETE(part);
}

void ModelMesh::Update()
{
	BoneInfo.BoneIndex = BoneIndex;

	//perframe->Update();

	for (ModelMeshPart* part : MeshParts)
		part->Update();
}

void ModelMesh::Render()
{
	// SetVS���� PS���� CS���� �ľ� �ȵǼ� �ϴ� ����
	//BoneBuffer->Set

	// WorldBuffer�� ���� ����� �ҵ�
	// PerFrame->Update();

	VBuffer->Set();
	IBuffer->Set();

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (ModelMeshPart* part : MeshParts)
		part->Render();
}

void ModelMesh::Render(UINT DrawCount)
{
	// SetVS���� PS���� CS���� �ľ� �ȵǼ� �ϴ� ����
	//BoneBuffer->Set

	// WorldBuffer�� ���� ����� �ҵ�
	// PerFrame->Update();

	VBuffer->Set();
	IBuffer->Set();

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (ModelMeshPart* part : MeshParts)
		part->Render(DrawCount);
}

void ModelMesh::Binding()
{
	// �ϴ� ����
}

void ModelMesh::SetShader(wstring ShaderFile)
{
	/*
	* Safe_Delete(PerFrame);
	* PerFrame = new PerFrame(ShaderFile);
	*/

	for (ModelMeshPart* part : MeshParts)
		part->SetShader(ShaderFile);
}
