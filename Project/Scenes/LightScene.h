#pragma once

class LightBuffer : public ConstBuffer
{
public:
	struct LightData
	{
	public:
		Vector4 Ambient = Vector4(0.1f, 0.1, 0.1, 1.0f);
		Vector4 Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		Vector4 Specular = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		Vector3 Direction = Vector3(0.0f, 0.0f, -1.0f);
	private:
		float Padding1;
	public:
		Vector3 Position = Vector3(0.0f, 10.0f, 0.0f);
	private:
		float Padding2;
	};

public:
	LightBuffer() : ConstBuffer(&Data, sizeof(LightData)) {}
	LightData& Get() { return Data; }

private:
	LightData Data;
};

class LightScene : public Scene
{
public:
	LightScene();
	~LightScene();

	void Initialize() override;
	void Disable() override {};
	void Destroy() override;

	void Update() override;

	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

	void UIRender() override {}
	void GUIRender() override;

	void ResizeScreen() override {};

private:
	//class TestObject* Object[2];
	class Box* Object;
	class Terrain* Field;

	vector<Box*> Objects;
	Box* Light = nullptr;

	LightBuffer::LightData LightDesc;
	LightBuffer* LBuffer = nullptr;
};

