#pragma once

class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();

	void Initialize() override;
	void Disable() override {};
	void Destory() override;

	void Update() override;

	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

	void UIRender() override {}
	void GUIRender() override;

	void ResizeScreen() override {};

private:
	class TestObject* Object[2];
	class Terrain* Field;
};

