#pragma once

#define MAX_MODEL_TRANSFORMS 250
#define MAX_MODEL_KEYFRAMES 500
#define MAX_MODEL_INSTANCE 500

struct InstanceDesc
{
	int IndexCount = 0;
};

class InstanceManager
{
private:
	InstanceManager();
	~InstanceManager();

public:
	static InstanceManager* Get();
	static void Destroy();

	//void Update();
	void Render();
	void Push(Transformation* Transform);

	//private:
	//	void CreateTexture();

private:
	static InstanceManager* Instance;

	UINT Size = 0;

	vector<Matrix> Worlds;
	vector<Transformation*> Transforms;
	//map<string, vector<InstanceDesc>> Desc;

	//unordered_map<string, int> IndexCounts;
	//unordered_map<string, vector<Transformation*>> Transforms;

	VertexBuffer* InstanceBuffer = nullptr;

	//ID3D11Texture2D* Texture;
	//ID3D11ShaderResourceView* TransformsSRV;
};

