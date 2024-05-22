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

/*
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
	SAFE_RELEASE(DepthStencilView);
	SAFE_RELEASE(DepthStencilState);
}

D3D* D3D::Get()
{
	if (Instance == nullptr)
		Instance = new D3D();

	return Instance;
}

void D3D::Create()
{
	DeviceSetting();
	BackBufferSetting();
	DepthStencilViewSetting();
	DepthStencilStateSetting();
	ViewportSetting();
}

void D3D::Destroy()
{
	delete Instance;
}

void D3D::Clear()
{
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);
	DeviceContext->OMSetDepthStencilState(DepthStencilState, 1);

	float clearColor[4] = { Desc.Background.x, Desc.Background.y, Desc.Background.z, Desc.Background.w };
	DeviceContext->ClearRenderTargetView(RenderTargetView, clearColor);
	DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3D::Present()
{
	SwapChain->Present(0, 0);
}

void D3D::DeviceSetting()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferDesc.Width = WIN_WIDTH;
	desc.BufferDesc.Height = WIN_HEIGHT;
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
}

void D3D::BackBufferSetting()
{
	ID3D11Texture2D* backBuffer;

	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
	backBuffer->Release();

	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
}

void D3D::DepthStencilViewSetting()
{
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthDesc.Width = WIN_WIDTH;
	depthDesc.Height = WIN_HEIGHT;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	ID3D11Texture2D* depthBuffer;
	Device->CreateTexture2D(&depthDesc, nullptr, &depthBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvDesc.Format = depthDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	Device->CreateDepthStencilView(depthBuffer, &dsvDesc, &DepthStencilView);
	depthBuffer->Release();
}

void D3D::DepthStencilStateSetting()
{
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = false;

	Device->CreateDepthStencilState(&dsDesc, &DepthStencilState);
}

void D3D::ViewportSetting()
{
	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<FLOAT>(WIN_WIDTH);
	viewport.Height = static_cast<FLOAT>(WIN_HEIGHT);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	DeviceContext->RSSetViewports(1, &viewport);
}

*/