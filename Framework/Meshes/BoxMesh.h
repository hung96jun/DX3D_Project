#pragma once

#include "Mesh.h"

class BoxMesh : public Mesh
{
public:
	BoxMesh();
	~BoxMesh();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

};