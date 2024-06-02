#include "Framework.h"
#include "RasterizerState.h"
#include "Systems/D3D.h"

RasterizerState::RasterizerState()
{
	CONSTRUCTOR_DEBUG();

	Desc.CullMode = D3D11_CULL_BACK;
	//Desc.CullMode = D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_SOLID;

	Changed();
}

RasterizerState::~RasterizerState()
{
	DESTRUCTOR_DEBUG();

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
