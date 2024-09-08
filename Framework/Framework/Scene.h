#pragma once

class Scene
{
public:
	virtual ~Scene() {};

	virtual void Initialize() = 0;
	virtual void Disable() = 0;
	virtual void Destroy() = 0;

	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual void UIRender() = 0;
	virtual void GUIRender() = 0;

	virtual void ResizeScreen() = 0;

	void OnActive() { bActive = true; }
	void OnDisable() { bActive = false; }
	const bool IsActive() const { return bActive; }

private:
	bool bActive = false;
};