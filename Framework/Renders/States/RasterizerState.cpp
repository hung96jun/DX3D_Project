#include "Framework.h"
#include "RasterizerState.h"
#include "Systems/D3D.h"

RasterizerState::RasterizerState()
{
	Desc.CullMode = D3D11_CULL_BACK;
	Desc.FillMode = D3D11_FILL_SOLID;

	Changed();
}

RasterizerState::~RasterizerState()
{
	SAFE_RELEASE(State);
}

void RasterizerState::SetState()
{
	D3D::GetDC()->RSSetState(State);
}

void RasterizerState::FillMode(D3D11_FILL_MODE Value)
{
	Desc.FillMode = Value;

	Changed();
}

void RasterizerState::FrontCounterClockwise(bool Value)
{
	Desc.FrontCounterClockwise = Value;

	Changed();
}

void RasterizerState::Changed()
{
	if (State != nullptr)
		SAFE_RELEASE(State);

	D3D::GetDevice()->CreateRasterizerState(&Desc, &State);
}
