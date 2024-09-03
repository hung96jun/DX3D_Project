#pragma once

#include "Objects/Base/ShapeObject.h"

class BoxShape;

class Box : public ShapeObject
{
public:
	Box();
	Box(const wstring ShaderFile);
	~Box();

	virtual void Initialize() override {}
	virtual void Update() override;
	virtual void PreRender()  override {}
	virtual void Render() override;
	virtual void PostRender()  override {}
	virtual void GUIRender() override;
};