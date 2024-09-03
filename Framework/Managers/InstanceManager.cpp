#include "Framework.h"
#include "InstanceManager.h"

InstanceManager* InstanceManager::Instance = nullptr;

InstanceManager::InstanceManager()
{
	CONSTRUCTOR_DEBUG();

	Worlds.resize(MAX_MODEL_INSTANCE);
	InstanceBuffer = new VertexBuffer(Worlds.data(), sizeof(Matrix), MAX_MODEL_INSTANCE, true, false);
}

InstanceManager::~InstanceManager()
{
	DESTRUCTOR_DEBUG();

	SAFE_DELETE(InstanceBuffer);
}

InstanceManager* InstanceManager::Get()
{
	if (Instance == nullptr)
		Instance = new InstanceManager();

	return Instance;
}

void InstanceManager::Destroy()
{
	delete Instance;
}

//void InstanceManager::Update()
//{
//	for (Transformation* transform : Transforms)
//		transform->Update();
//}

void InstanceManager::Render()
{
	{
		if (Transforms.size() != Worlds.size())
			Worlds.resize(Transforms.size());
		
		transform(Transforms.begin(), Transforms.end(), Worlds.begin(),
			[](Transformation* t) { return t->GetWorld(); });
		
		InstanceBuffer->Update(Worlds.data(), MAX_MODEL_INSTANCE);
		InstanceBuffer->Set(1);
		
		// param0	index count
		D3D::GetDC()->DrawIndexedInstanced(36, Transforms.size(), 0, 0, 0);
	}

	//{
	//	for (pair<string, int> desc : IndexCounts)
	//	{
	//		string tag = desc.first;
	//		if (Transforms[tag].size() != Worlds.size())
	//			Worlds.resize(Transforms[tag].size());

	//		transform(Transforms[tag].begin(), Transforms[tag].end(), Worlds.begin(),
	//			[](Transformation* t) {return t->GetWorld(); });

	//		InstanceBuffer->Update(Worlds.data(), MAX_MODEL_INSTANCE);
	//		InstanceBuffer->Set(1);

	//		D3D::GetDC()->DrawIndexedInstanced(desc.second, Transforms[tag].size(), 0, 0, 0);
	//	}
	//}
}

void InstanceManager::Push(Transformation* Transform)
{
	Transforms.push_back(Transform);
}

//void InstanceManager::CreateTexture()
//{
//	D3D11_TEXTURE2D_DESC desc;
//	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
//	desc.Width = MAX_MODEL_TRANSFORMS * 4;
//	desc.Height = MAX_MODEL_INSTANCE;
//	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//	desc.Usage = D3D11_USAGE_DYNAMIC;
//	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//	desc.MipLevels = 1;
//	desc.ArraySize = 1;
//	desc.SampleDesc.Count = 1;
//
//	D3D11_SUBRESOURCE_DATA data;
//	data.pSysMem = Worlds.data();
//	data.SysMemPitch = sizeof(Matrix);
//	data.SysMemSlicePitch = sizeof(Matrix) * MAX_MODEL_INSTANCE;
//
//	CHECK(D3D::GetDevice()->CreateTexture2D(&desc, &data, &Texture));
//
//	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
//	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//	srvDesc.Texture2D.MipLevels = 1;
//	srvDesc.Format = desc.Format;
//
//	CHECK(D3D::GetDevice()->CreateShaderResourceView(Texture, &srvDesc, &TransformsSRV));
//}
