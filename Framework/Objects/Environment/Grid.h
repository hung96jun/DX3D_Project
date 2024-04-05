#pragma once
#include "Objects/Object.h"

class Grid : public Object
{
public:
	Grid(const UINT Width = 255.0f, const UINT Height = 255.0f);
	virtual ~Grid();

	void Update() override {}
	void PreRender() override {}
	void Render() override;
	void PostRender() override {}
	void GUIRender() override;

private:
	UINT Width = 255, Height = 255;

	MatrixBuffer* WBuffer;
};

