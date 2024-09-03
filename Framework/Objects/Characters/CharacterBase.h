#pragma once

#include "../Actor.h"

class Model;

class CharacterBase : public Actor
{
public:
	CharacterBase(const wstring ShaderFile = L"SimpleShader");
	~CharacterBase();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void GUIRender() override;

private:
	Model* Skin = nullptr;
};

