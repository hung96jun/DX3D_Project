#pragma once
#include "Systems/Scene.h"

class TestScene : public Scene
{
public:
	virtual void Initializer() override;
	//virtual void Ready() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ResizeScreen() override;

private:

};

