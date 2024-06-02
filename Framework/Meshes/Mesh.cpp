#include "Mesh.h"

Mesh::Mesh(const wstring VertexShader)
{
	VShader = ShaderManager::Get()->AddVS(VertexShader);
}

Mesh::~Mesh()
{
	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void Mesh::Update()
{
	Transform.Update();
}

void Mesh::Render()
{
	if (VBuffer == nullptr || IBuffer == nullptr)
		return;

	WBuffer->Set(Transform.GetWorld());
	WBuffer->SetVS(0);

	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}

void Mesh::GUIRender()
{
	if (ImGui::TreeNode("Mesh Info"))
	{
		if (ImGui::Begin((Transform.GetTag() + "_Mesh").c_str()))
		{
			Transform.GUIRender();

			ImGui::End();
		}

		ImGui::TreePop();
	}
}

void Mesh::SetPosition(const Vector3 Pos)
{
	Transform.SetPosition(Pos);
}

void Mesh::SetRotation(const Vector3 Rot)
{
	Transform.SetRotation(Rot);
}

void Mesh::SetScale(const Vector3 Scale)
{
	Transform.SetScale(Scale);
}

void Mesh::AddPosition(const Vector3 Pos)
{
	Vector3 pos = Transform.GetPosition();
	pos += Pos;
	Transform.SetPosition(pos);
}

void Mesh::AddRotation(const Vector3 Rot)
{
	Vector3 rot = Transform.GetRotation();
	rot += Rot;
	Transform.SetRotation(rot);
}

void Mesh::AddScale(const Vector3 Scale)
{
	Vector3 scale = Transform.GetScale();
	scale += Scale;
	Transform.SetScale(scale);
}

void Mesh::SetVertices(vector<VertexMesh> Vertices, vector<int> Indices)
{
	this->Vertices = Vertices;
	VBuffer = new VertexBuffer(this->Vertices.data(), sizeof(VertexMesh), static_cast<UINT>(this->Vertices.size()));

	this->Indices = Indices;
	IBuffer = new IndexBuffer(this->Indices.data(), static_cast<UINT>(this->Indices.size()));
}
