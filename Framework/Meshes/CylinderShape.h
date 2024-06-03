#pragma once

#include "Shape.h"

class CyllinderShape : public Shape
{
public:
	CyllinderShape();
	~CyllinderShape();

	void Resize();
	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;

private:
	void Create();
	void TopCap();
	void BottomCap();
};