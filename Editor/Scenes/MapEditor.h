#pragma once

class MapEditor : public Scene
{
public:
	MapEditor();
	~MapEditor();

	void Initialize() override;
	void Disable() override;
	void Destory() override;

	void Update() override;

	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void GUIRender() override;

	void ResizeScreen() override;

};

