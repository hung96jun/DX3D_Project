#pragma once

class ModelExporter;

class ModelEditor : public Scene
{
public:
	ModelEditor();
	~ModelEditor();

	void Initialize() override {}
	void Disable() override {}
	void Destory() override {}
	void Update() override {}
	void PreRender() override {}
	void Render() override {}
	void PostRender() override {}
	void UIRender() override {}
	void GUIRender() override;
	void ResizeScreen() override;

private:
	ModelExporter* Exporter;
};

