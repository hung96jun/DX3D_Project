#pragma once

#include "Objects/Actor.h"

class Shape;

class ShapeObject : public Actor
{
public:
	ShapeObject();
	virtual ~ShapeObject();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender()  override {}
	virtual void Render() override;
	virtual void PostRender()  override {}
	virtual void GUIRender() override;

	void SetTag(const string Tag);

protected:
	Shape* Mesh = nullptr;
	Material* Mat = nullptr;
};