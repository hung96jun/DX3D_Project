#pragma once

class Viewport
{
public:
	Viewport() = delete;
	Viewport(float Width, float Height, float X = 0.0f, float Y = 0.0f, float MinDepth = 0.0f, float MaxDepth = 0.0f);
	~Viewport();

	void RSSetViewport();
	void Set(float Width, float Height, float X = 0.0f, float Y = 0.0f, float MinDepth = 0.0f, float MaxDepth = 0.0f);

	float GetWidth() { return Width; }
	float GetHeight() { return Height; }

private:
	float X, Y;
	float Width, Height;
	float MinDepth, MaxDepth;

	D3D11_VIEWPORT View;
};

