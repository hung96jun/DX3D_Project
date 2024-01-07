#include "Framework.h"
#include "D3D.h"

D3D* D3D::Instance = nullptr;

D3DDesc D3D::Desc;
ID3D11Device* D3D::Device = nullptr;
ID3D11DeviceContext* D3D::DeviceContext = nullptr;
IDXGISwapChain* D3D::SwapChain = nullptr;

D3D::D3D()
	:Numerator(0), Denominator(1)
{
	SetGPUInfo();
	CreateSwapChainAndDevice();
	CreateVackBuffer(Desc.Width, Desc.Height);
}

D3D::~D3D()
{
	DeleteBackBuffer();

	if (SwapChain != nullptr)
		SwapChain->SetFullscreenState(false, nullptr);

	SAFE_RELEASE(DeviceContext);
	SAFE_RELEASE(Device);
	SAFE_RELEASE(SwapChain);
}

void D3D::SetGPUInfo()
{
	HRESULT hResult;

	IDXGIFactory* factory;
	hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	CHECK(hResult);

	IDXGIAdapter* adapter;
	hResult = factory->EnumAdapters(0, &adapter);
	CHECK(hResult);

	IDXGIOutput* adapterOutput;
	hResult = adapter->EnumOutputs(0, &adapterOutput);
	CHECK(hResult);

	UINT modeCount = 0;
	hResult = adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		nullptr
	);
	CHECK(hResult);

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[modeCount];
	hResult = adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		displayModeList
	);
	CHECK(hResult);

	for (UINT i = 0; i < modeCount; i++)
	{
		bool bCheck = true;
		bCheck &= displayModeList[i].Width == Desc.Width;		// 오류 발생할 가능성 있으므로 나중에 테스트 후 확인
		bCheck &= displayModeList[i].Height == Desc.Height;

		if (bCheck == true)
		{
			Numerator = displayModeList[i].RefreshRate.Numerator;
			Denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	hResult = adapter->GetDesc(&adapterDesc);
	CHECK(hResult);

	GPUMenorySize = static_cast<UINT>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
	GPUDescriptoin = adapterDesc.Description;

	SAFE_DELETE_ARRAY(displayModeList);

	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);
}

void D3D::CreateSwapChainAndDevice()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (Desc.bVsync == true)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = Numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = Denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = Desc.Handle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !Desc.bFullScreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	HRESULT hResult = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&SwapChain,
		&Device,
		nullptr,
		&DeviceContext
	);
	CHECK(hResult);
}

void D3D::CreateVackBuffer(float width, float height)
{
	HRESULT hResult;

	{
		ID3D11Texture2D* backBuffer;
		hResult = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		CHECK(hResult);

		hResult = Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
		CHECK(hResult);

		SAFE_RELEASE(backBuffer);
	}

	{
		D3D11_TEXTURE2D_DESC desc = { 0 };
		desc.Width = static_cast<UINT>(width);
		desc.Height = static_cast<UINT>(height);
		desc.MipLevels = 1;
		desc.BindFlags = 1;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		hResult = Device->CreateTexture2D(&desc, nullptr, &BackBuffer);
		CHECK(hResult);
	}

	{
		D3D11_DEPTH_STENCIL_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		hResult = Device->CreateDepthStencilView(BackBuffer, &desc, &DepthStencilView);
		CHECK(hResult);

		SetRendertarget(RenderTargetView, DepthStencilView);
	}
}

void D3D::DeleteBackBuffer()
{
	SAFE_RELEASE(DepthStencilView);
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(BackBuffer);
}

D3D* D3D::Get()
{
	assert(Instance != nullptr);
	return Instance;
}

void D3D::Create()
{
	assert(Instance == nullptr);
	Instance = new D3D();
}

void D3D::Delete()
{
	SAFE_DELETE(Instance);
}

void D3D::SetRendertarget(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	if (rtv == nullptr)
		rtv = RenderTargetView;
	if (dsv == nullptr)
		dsv = DepthStencilView;

	DeviceContext->OMSetRenderTargets(1, &rtv, dsv);
}

void D3D::Clear(Color color, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	if (rtv == nullptr)
		rtv = RenderTargetView;
	if (dsv == nullptr)
		dsv = DepthStencilView;

	float clearColor[4] = { color.R, color.G, color.B, color.A };

	DeviceContext->ClearRenderTargetView(rtv, clearColor);
	DeviceContext->ClearDepthStencilView(dsv, D3D10_CLEAR_DEPTH, 1, 0);
}

void D3D::Present()
{
	SwapChain->Present(Desc.bVsync == true ? 1 : 0, 0);
}

void D3D::ResizeScreen(float width, float height)
{
	if (width < 1 || height < 1)
		return;

	Desc.Width = width;
	Desc.Height = height;

	DeleteBackBuffer();

	HRESULT hResult = SwapChain->ResizeBuffers(0, static_cast<UINT>(width), static_cast<UINT>(height), DXGI_FORMAT_UNKNOWN, 0);
	CHECK(hResult);

	CreateVackBuffer(width, height);
}
