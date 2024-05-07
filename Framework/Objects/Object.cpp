#include "Object.h"

Object::Object(const wstring ShaderFile)
{
	CONSTRUCTOR_DEBUG();

	VShader = ShaderManager::Get()->AddVS(ShaderFile);
	PShader = ShaderManager::Get()->AddPS(ShaderFile);

	//Vertices.emplace_back(+0.0f, +0.0f, 0.0f, 0.5f, 0.5f, 1.0f);
	//Vertices.emplace_back(+0.5f, +0.0f, 0.0f, 0.5f, 0.5f, 1.0f);
	//Vertices.emplace_back(+0.0f, +0.5f, 0.0f, 0.5f, 0.5f, 1.0f);
	//Vertices.emplace_back(+0.5f, +0.5f, 0.0f, 0.5f, 0.5f, 1.0f);
	//Vertices.emplace_back(+0.0f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f);
	//Vertices.emplace_back(+0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f);

	Vertices.emplace_back(+0.0f, +0.5f, +1.0f, 0.5f, 0.5f, 1.0f);
	Vertices.emplace_back(+0.5f, -0.5f, +1.0f, 0.5f, 0.5f, 1.0f);
	Vertices.emplace_back(-0.5f, -0.5f, +1.0f, 0.5f, 0.5f, 1.0f);

	//Indices = { 0, 1, 2, 2, 1, 3 };

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexColor), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), sizeof(Indices.size()));
	WBuffer = new WorldBuffer();
}

Object::~Object()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);
}

void Object::Update()
{
	//Transform.Update();

	Matrix s, r, t;
	s = XMMatrixScaling(Transform.GetScale().X, Transform.GetScale().Y, Transform.GetScale().Z);
	r = XMMatrixRotationZ(0.0f);
	t = XMMatrixTranslation(Transform.GetPosition().X, Transform.GetPosition().Y, Transform.GetPosition().Z);

	Matrix mat = s * r * t;

	WBuffer->Set(mat);
}

void Object::Render()
{
	WBuffer->Set(Transform.GetWorld());
	WBuffer->SetVS(0);

	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->Draw(static_cast<UINT>(Vertices.size()), 0);
}

void Object::GUIRender()
{	
	if (ImGui::TreeNode((GetTag() + "Object").c_str()))
	{
		string temp = "";
		temp += "GlobalPos : " + Transform.GetGlobalPosition().ToString();
		temp += "\nGlobalScale : " + Transform.GetGlobalScale().ToString();
		ImGui::Text(temp.data());

		Transform.GUIRender();
	}
}
