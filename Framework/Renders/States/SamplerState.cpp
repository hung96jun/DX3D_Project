#include "Framework.h"
#include "SamplerState.h"
#include "Systems/D3D.h"

SamplerState::SamplerState()
{
	Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	Desc.MinLOD = 0;
	Desc.MaxLOD = D3D11_FLOAT32_MAX;

	Changed();
}

SamplerState::~SamplerState()
{
	SAFE_RELEASE(State);
}

void SamplerState::SetState(UINT Slot)
{
	D3D::GetDC()->PSSetSamplers(Slot, 1, &State);
}

void SamplerState::Filter(D3D11_FILTER Value)
{
	Desc.Filter = Value;
	Changed();
}

void SamplerState::Changed()
{
	if (State != nullptr)
		SAFE_RELEASE(State);

	D3D::GetDevice()->CreateSamplerState(&Desc, &State);
}
