#pragma once

// Pure Class
class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void GUIRender() = 0;
};