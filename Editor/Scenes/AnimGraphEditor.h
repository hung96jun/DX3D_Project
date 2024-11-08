#pragma once


class AnimGraphEditor : public Scene
{
public:
	AnimGraphEditor();
	~AnimGraphEditor();

	void Initialize() override;
	void Disable() override;
	void Destroy() override;

	void Update() override;

	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void GUIRender() override;

	void ResizeScreen() override;
};

