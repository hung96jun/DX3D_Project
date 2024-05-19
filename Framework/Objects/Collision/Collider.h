#pragma once
#include "Objects/Object.h"

class Collider : public Object
{
public:
	Collider(const wstring ShaderFile = L"SimpleShader");
	virtual ~Collider();

	virtual void Update();
	virtual void PreRender() {}
	virtual void Render();
	virtual void PostRender() {}
	virtual void GUIRender();

private:

};

