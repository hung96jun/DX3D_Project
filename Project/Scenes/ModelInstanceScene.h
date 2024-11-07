#pragma once

class ModelInstanceScene : public Scene
{
public:
	void Initialize() override;
	void Disable() override {}
	void Destroy() override;
	void Update() override;
	void PreRender() override {}
	void Render() override;
	void PostRender() override {}
	void UIRender() override {}
	void GUIRender() override;
	void ResizeScreen() override {}
	
private:
	Model* TestModel;
	//Model* TestModel1;

	vector<Transformation> Transforms;
	vector<Matrix> Instances;

	VertexBuffer* InstanceBuffer = nullptr;

	const UINT Count = 10;
};

