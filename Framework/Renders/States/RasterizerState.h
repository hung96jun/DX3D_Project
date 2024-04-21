#pragma once

class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void SetState();

	void FillMode(D3D11_FILL_MODE Value);
	void FrontCounterClockwise(bool Value);

	void Changed();

private:
	D3D11_RASTERIZER_DESC Desc = {};
	ID3D11RasterizerState* State = nullptr;
};

