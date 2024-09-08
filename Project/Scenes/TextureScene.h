#pragma once

#define INSTANCE_TEST 1

class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();

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
};

