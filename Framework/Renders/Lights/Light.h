#pragma once
#include "Objects/Actor.h"
#include "Framework/Buffers/ConstBuffer.h"

//struct LightDesc
//{
//	LightDesc() {}
//	LightDesc(const Color Ambient, const Color Specular, const Vector3 Direction, const Vector3 Position)
//		: Ambient(Ambient), Specular(Specular), Direction(Direction), Position(Position) {}
//
//public:
//	Color Ambient = Color(0.0f);
//	Color Specular = Color(0.0f);
//	Vector3 Direction = Vector3(0.0f);
//private:
//	float Padding1 = 0.0f;
//public:
//	Vector3 Position = Vector3(0.0f);
//private:
//	float Padding2 = 0.0f;
//};

class Light : public Object
{
public:
	Light();
	virtual ~Light();

	virtual void Initialize() override {}
	virtual void Update() override {}
	virtual void PreRender() override {}
	virtual void Render() override {}
	virtual void PostRender() override {}
	virtual void GUIRender() override {}

	Color& GetAmbient() { return Ambient; }
	Color& GetDiffuse() { return Diffuse; }
	Color& GetSpecular() { return Specular; }
	Vector3& GetDirection() { return Direction; }
	//Vector3& GetPosition() { return Position; }

protected:
	ConstBuffer* LightBuffer = nullptr;

	Color Ambient = Color(0.0f);
	Color Diffuse = Color(0.0f);
	Color Specular = Color(0.0f);
	Vector3 Direction = Vector3(0.0f);
	//Vector3 Position = Vector3(0.0f);

//private:
//	LightDesc Desc;
};