#pragma once

class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void SetState(UINT Slot = 0);
	void Filter(D3D11_FILTER Value);

	void Changed();

private:
	D3D11_SAMPLER_DESC Desc = {};
	ID3D11SamplerState* State = nullptr;
};

