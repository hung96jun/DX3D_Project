#pragma once

class Object;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Initialize() override;
	void Disable() override {};
	void Destory() override;

	void Update() override;

	void PreRender() override {};
	void Render() override;
	void PostRender() override {};
	void GUIRender() override;

	void ResizeScreen() override {};

private:
	Object* TestObject = nullptr;
};

