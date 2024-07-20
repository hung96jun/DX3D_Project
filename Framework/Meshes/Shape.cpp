#include "Shape.h"

Shape::Shape(const wstring ShaderFile)
{
	CONSTRUCTOR_DEBUG();

	VShader = ShaderManager::Get()->AddVS(ShaderFile);
	WBuffer = new MatrixBuffer();
}

Shape::~Shape()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void Shape::Update()
{
	Transform.Update();
}

void Shape::Set()
{
	if (bHidden == true) return;
	if (VBuffer == nullptr || IBuffer == nullptr) return;

	bSet = true;

	WBuffer->Set(Transform.GetWorld());
	WBuffer->SetVS(0);

	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
}

void Shape::Render()
{
	if (bSet == false) return;
	bSet = false;

	D3D::GetDC()->DrawIndexed(static_cast<UINT>(Indices.size()), 0, 0);
}

void Shape::GUIRender()
{
	Transform.GUIRender();
}

void Shape::SetPosition(const Vector3 Pos)
{
	Transform.SetPosition(Pos);
}

void Shape::SetRotation(const Vector3 Rot)
{
	Transform.SetRotation(Rot);
}

void Shape::SetScale(const Vector3 Scale)
{
	Transform.SetScale(Scale);
}

void Shape::AddPosition(const Vector3 Pos)
{
	Vector3 pos = Transform.GetPosition();
	pos += Pos;
	Transform.SetPosition(pos);
}

void Shape::AddRotation(const Vector3 Rot)
{
	Vector3 rot = Transform.GetRotation();
	rot += Rot;
	Transform.SetRotation(rot);
}

void Shape::AddScale(const Vector3 Scale)
{
	Vector3 scale = Transform.GetScale();
	scale += Scale;
	Transform.SetScale(scale);
}

void Shape::SetVertices(vector<VertexMesh> Vertices, vector<UINT> Indices)
{
	if (VBuffer == nullptr)
	{
		this->Vertices = Vertices;
		VBuffer = new VertexBuffer(this->Vertices.data(), sizeof(VertexMesh), static_cast<UINT>(Vertices.size()));

		this->Indices = Indices;
		IBuffer = new IndexBuffer(this->Indices.data(), static_cast<UINT>(this->Indices.size()));
	}

	else
	{
		this->Vertices = Vertices;
		VBuffer->Update(this->Vertices.data(), static_cast<UINT>(this->Vertices.size()));

		if (Indices.size() > 0)
		{
			this->Indices = Indices;
			IBuffer->Update(this->Indices.data(), static_cast<UINT>(this->Indices.size()));
		}
	}
}

void Shape::Resize()
{
	VBuffer->Update(Vertices.data(), static_cast<UINT>(Vertices.size()));
	IBuffer->Update(Indices.data(), static_cast<UINT>(Indices.size()));
}
