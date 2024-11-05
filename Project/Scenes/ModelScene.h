#pragma once

class ModelScene : public Scene
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

	vector<Transformation> Transforms;
};

