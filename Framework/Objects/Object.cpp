#include "Object.h"

Object::Object(const wstring ShaderFile)
{
	VShader = ShaderManager::Get()->AddVS(ShaderFile + L".hlsl");
	PShader = ShaderManager::Get()->AddPS(ShaderFile + L".hlsl");

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
	//WBuffer->Set(XMMatrixIdentity());
	WBuffer->SetVS(0);

	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->Draw(Vertices.size(), VertexStart);
	//D3D::GetDC()->DrawIndexed(Indices.size(), 0, 0);
}

void Object::GUIRender()
{	
	//ImGui::Begin("Vertex");

	ImGui::InputInt("VertexStart", &VertexStart);
	VertexStart %= Vertices.size() - 1;

	string temp = "";
	temp += "GlobalPos : " + Transform.GetGlobalPosition().ToString();
	temp += "\nGlobalScale : " + Transform.GetGlobalScale().ToString();
	ImGui::Text(temp.data());

	if (ImGui::TreeNode("Object Transform"))
	{
		float pos[3];
		pos[0] = Transform.GetPosition().X;
		pos[1] = Transform.GetPosition().Y;
		pos[2] = Transform.GetPosition().Z;

		ImGui::DragFloat3("Position", pos, 0.01f, -1.0f, 1.0f);
		Transform.SetPosition(Vector3(pos[0], pos[1], pos[2]));

		float scale[3];
		scale[0] = Transform.GetScale().X;
		scale[1] = Transform.GetScale().Y;
		scale[2] = Transform.GetScale().Z;

		ImGui::DragFloat3("Scale", scale, 0.01f, -1.0f, 1.0f);
		Transform.SetScale(Vector3(scale[0], scale[1], scale[2]));

		ImGui::TreePop();
	}

	//ImGui::End();
}
