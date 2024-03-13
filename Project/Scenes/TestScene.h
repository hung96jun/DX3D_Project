#pragma once
#include "Systems/Scene.h"

class Test;

class TestScene : public Scene
{
public:
	virtual void Initializer() override;
	virtual void Ready() override {}
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {} 
	virtual void ResizeScreen() override {}

private:
	Object* Test;

	//VertexShader* VShader = nullptr;

	//Vertex Vertices[3];
	//ID3D11Buffer* VBuffer;

	VertexShader* VShader = nullptr;
	XMFLOAT3 vertices[3];
	ID3D11Buffer* pVertexBuffer;
};

