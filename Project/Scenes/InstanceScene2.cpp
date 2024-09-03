#include "stdafx.h"
#include "InstanceScene2.h"

void InstanceScene2::Initialize()
{
	VShader = ShaderManager::Get()->AddVS(L"TestInstanceShader2");
	PShader = ShaderManager::Get()->AddPS(L"TestInstanceShader2");

	CreateMesh(Vector3(1.0f));

	VBuffer = new VertexBuffer(Vertices.data(), sizeof(VertexUV), static_cast<UINT>(Vertices.size()));
	IBuffer = new IndexBuffer(Indices.data(), static_cast<UINT>(Indices.size()));
	WBuffer = new MatrixBuffer();

	Instances.resize(Count);

	for (int i = 0; i < Count; i++)
	{
		Transformation transform;
		transform.SetPosition(Math::RandomVector3(20, -20));
		transform.SetScale(Math::RandomVector3(5, 1));

		//Vector3 pos = Vector3::ZeroVector();
		//pos.X += (2 * i);

		//transform.SetPosition(pos);
		//transform.SetScale(Vector3(1.0f));

		transform.Update();

		Transforms.push_back(transform);

		InstData data;
		data.Vec1 = DivisionMatrix(transform.GetWorld(), 0);
		data.Vec2 = DivisionMatrix(transform.GetWorld(), 1);
		data.Vec3 = DivisionMatrix(transform.GetWorld(), 2);
		data.Vec4 = DivisionMatrix(transform.GetWorld(), 3);

		Instances.push_back(data);
	}
	
	//Instances.resize(Transforms.size());
	//transform(Transforms.begin(), Transforms.end(), Instances.begin(),
	//	[](Transformation t) { return t.GetWorld(); });

	InstanceBuffer = new VertexBuffer(Instances.data(), sizeof(InstData), Count);

	Mat = new Material();
	Mat->SetDiffuseMap(L"Color/Test.png");
}

void InstanceScene2::Destory()
{
	SAFE_DELETE(VBuffer);
	SAFE_DELETE(IBuffer);
	SAFE_DELETE(WBuffer);

	SAFE_DELETE(Mat);

	SAFE_DELETE(InstanceBuffer);
}

void InstanceScene2::Update()
{
	transform(Transforms.begin(), Transforms.end(), Instances.begin(),
		[](Transformation t) 
		{
			InstData data;
			data.Vec1 = DivisionMatrix(t.GetWorld(), 0);
			data.Vec2 = DivisionMatrix(t.GetWorld(), 1);
			data.Vec3 = DivisionMatrix(t.GetWorld(), 2);
			data.Vec4 = DivisionMatrix(t.GetWorld(), 3);

			return data;
		});
}

void InstanceScene2::Render()
{
	VBuffer->Update(Vertices.data(), Vertices.size());
	InstanceBuffer->Update(Instances.data(), Count);
	InstanceBuffer->Set(1);

	Mat->Set();
	VBuffer->Set();
	IBuffer->Set();

	VShader->Set();
	PShader->Set();

	D3D::GetDC()->DrawIndexedInstanced(Indices.size(), Instances.size(), 0, 0, 0);
}

void InstanceScene2::GUIRender()
{
	for (int i = 0; i < Transforms.size(); i++)
	{
		float pos[3] = { Transforms[i].GetPosition().X, Transforms[i].GetPosition().Y, Transforms[i].GetPosition().Z };
		ImGui::SliderFloat3(("Position_" + to_string(i)).c_str(), pos, -50.0f, 50.0f);
		Transforms[i].SetPosition(Vector3(pos[0], pos[1], pos[2]));

		float scale[3] = { Transforms[i].GetScale().X, Transforms[i].GetScale().Y, Transforms[i].GetScale().Z };
		ImGui::SliderFloat3(("Scale_" + to_string(i)).c_str(), scale, -10.0f, 10.0f);
		Transforms[i].SetScale(Vector3(scale[0], scale[1], scale[2]));

		float rot[3] = { Transforms[i].GetRotation().X, Transforms[i].GetRotation().Y, Transforms[i].GetRotation().Z };
		ImGui::SliderFloat3(("Rotation_" + to_string(i)).c_str(), rot, -360.0f, 360.0f);
		Transforms[i].SetRotation(Vector3(rot[0], rot[1], rot[2]));

		Transforms[i].Update();
	}
}

void InstanceScene2::CreateMesh(const Vector3 Size)
{
	float X, Y, Z;
	X = Size.X;
	Y = Size.Y;
	Z = Size.Z;

	vector<VertexUV> vertices;
	vector<UINT> indices;

	vertices.resize(4 * 6);
	{
		// Front
		vertices[0].Position = Vector3(-X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[1].Position = Vector3(-X * 0.5f, +Y * 0.5f, -Z * 0.5f);
		vertices[2].Position = Vector3(+X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[3].Position = Vector3(+X * 0.5f, +Y * 0.5f, -Z * 0.5f);

		vertices[0].Uv = Vector2(0.0f, 1.0f);
		vertices[1].Uv = Vector2(0.0f, 0.0f);
		vertices[2].Uv = Vector2(1.0f, 1.0f);
		vertices[3].Uv = Vector2(1.0f, 0.0f);

		// Back
		vertices[4].Position = Vector3(+X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[5].Position = Vector3(+X * 0.5f, +Y * 0.5f, +Z * 0.5f);
		vertices[6].Position = Vector3(-X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[7].Position = Vector3(-X * 0.5f, +Y * 0.5f, +Z * 0.5f);

		vertices[4].Uv = Vector2(0.0f, 1.0f);
		vertices[5].Uv = Vector2(0.0f, 0.0f);
		vertices[6].Uv = Vector2(1.0f, 1.0f);
		vertices[7].Uv = Vector2(1.0f, 0.0f);

		// Left
		vertices[8].Position = Vector3(-X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[9].Position = Vector3(-X * 0.5f, +Y * 0.5f, -Z * 0.5f);
		vertices[10].Position = Vector3(-X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[11].Position = Vector3(-X * 0.5f, +Y * 0.5f, +Z * 0.5f);

		vertices[8].Uv = Vector2(0.0f, 1.0f);
		vertices[9].Uv = Vector2(0.0f, 0.0f);
		vertices[10].Uv = Vector2(1.0f, 1.0f);
		vertices[11].Uv = Vector2(1.0f, 0.0f);


		// Right
		vertices[12].Position = Vector3(+X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[13].Position = Vector3(+X * 0.5f, +Y * 0.5f, +Z * 0.5f);
		vertices[14].Position = Vector3(+X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[15].Position = Vector3(+X * 0.5f, +Y * 0.5f, -Z * 0.5f);

		vertices[12].Uv = Vector2(0.0f, 1.0f);
		vertices[13].Uv = Vector2(0.0f, 0.0f);
		vertices[14].Uv = Vector2(1.0f, 1.0f);
		vertices[15].Uv = Vector2(1.0f, 0.0f);

		// Top
		vertices[16].Position = Vector3(+X * 0.5f, +Y * 0.5f, +Z * 0.5f);
		vertices[17].Position = Vector3(+X * 0.5f, +Y * 0.5f, -Z * 0.5f);
		vertices[18].Position = Vector3(-X * 0.5f, +Y * 0.5f, +Z * 0.5f);
		vertices[19].Position = Vector3(-X * 0.5f, +Y * 0.5f, -Z * 0.5f);

		vertices[16].Uv = Vector2(0.0f, 1.0f);
		vertices[17].Uv = Vector2(0.0f, 0.0f);
		vertices[18].Uv = Vector2(1.0f, 1.0f);
		vertices[19].Uv = Vector2(1.0f, 0.0f);

		// Top
		vertices[20].Position = Vector3(-X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[21].Position = Vector3(-X * 0.5f, -Y * 0.5f, -Z * 0.5f);
		vertices[22].Position = Vector3(+X * 0.5f, -Y * 0.5f, +Z * 0.5f);
		vertices[23].Position = Vector3(+X * 0.5f, -Y * 0.5f, -Z * 0.5f);

		vertices[20].Uv = Vector2(0.0f, 1.0f);
		vertices[21].Uv = Vector2(0.0f, 0.0f);
		vertices[22].Uv = Vector2(1.0f, 1.0f);
		vertices[23].Uv = Vector2(1.0f, 0.0f);

		indices =
		{
			0, 1, 2, 2, 1, 3,
			4, 5, 6, 6, 5, 7,
			11, 9, 10, 10, 9, 8,
			15, 13, 14, 14, 13, 12,
			16, 17, 18, 18, 17, 19,
			20, 21, 22, 22, 21, 23
		};
	}

	Vertices = vertices;
	Indices = indices;
}
