#include "D3D.h"

#include "Utilities/Debug.h"

D3D* D3D::Instance = nullptr;
ID3D11Device* D3D::Device = nullptr;
ID3D11DeviceContext* D3D::DeviceContext = nullptr;
WindowDesc D3D::Desc;

D3D::D3D()
{
	CONSTRUCTOR_DEBUG();
}

D3D::~D3D()
{
	DESTRUCTOR_DEBUG();

	SAFE_RELEASE(Device);
	SAFE_RELEASE(DeviceContext);

	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(RenderTargetView);
}

D3D* D3D::Get()
{
	if (Instance == nullptr)
		Instance = new D3D();

	return Instance;
}

void D3D::Create()
{
	UINT width = WIN_WIDTH;
	UINT height = WIN_HEIGHT;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.OutputWindow = Desc.Handle;
	desc.Windowed = true;//창모드 유무

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		&SwapChain,
		&Device,
		nullptr,
		&DeviceContext
	);

	ID3D11Texture2D* backBuffer;

	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
	backBuffer->Release();

	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<FLOAT>(width);
	viewport.Height = static_cast<FLOAT>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	DeviceContext->RSSetViewports(1, &viewport);
}

void D3D::Destroy()
{
	delete Instance;
}

void D3D::Clear()
{
	float clearColor[4] = { Desc.Background.x, Desc.Background.y, Desc.Background.z, Desc.Background.w };
	DeviceContext->ClearRenderTargetView(RenderTargetView, clearColor);
}

void D3D::Present()
{
	SwapChain->Present(0, 0);
}
