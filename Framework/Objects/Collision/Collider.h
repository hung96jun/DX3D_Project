#pragma once
#include "Objects/Actor.h"

class Collider : public Actor
{
public:
	Collider(const wstring ShaderFile = L"SimpleShader");
	virtual ~Collider();

	virtual void Initialize() override {}
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void GUIRender() override;

private:

};

