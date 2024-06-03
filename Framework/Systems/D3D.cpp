#include "D3D.h"

#include "Utilities/Debug.h"
#include "Utilities/stb_image.h"

D3D* D3D::Instance = nullptr;
ID3D11Device* D3D::Device = nullptr;
ID3D11DeviceContext* D3D::DeviceContext = nullptr;
WindowDesc D3D::Desc;

#if MODE == 1
IDXGISwapChain* D3D::SwapChain = nullptr;
#endif // MODE == 1

#if MODE == 0
D3D::D3D()
{
	CONSTRUCTOR_DEBUG();
}

D3D::~D3D()
{
	DESTRUCTOR_DEBUG();

	SAFE_RELEASE(Device);
	SAFE_RELEASE(DeviceContext);

	SAFE_RELEASE(DepthBuffer);

	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(DepthStencilView);
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
	HRESULT result;

	// Create Device & SwapChain
	{
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
	}

	// Get depthBuffer & Create RTV
	{
		ID3D11Texture2D* backBuffer;
		result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		CHECK(result);
		result = Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
		CHECK(result);
		SAFE_RELEASE(backBuffer);
	}

	// Create DepthStencilView
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = static_cast<UINT>(width);
		desc.Height = static_cast<UINT>(height);
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		result = Device->CreateTexture2D(&desc, nullptr, &DepthBuffer);
		CHECK(result);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

		result = Device->CreateDepthStencilView(DepthBuffer, &dsvDesc, &DepthStencilView);
		CHECK(result);

		SetRenderTarget(RenderTargetView, DepthStencilView);
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_LESS;

		ID3D11DepthStencilState* state;
		result = Device->CreateDepthStencilState(&desc, &state);
		DeviceContext->OMSetDepthStencilState(state, 1);
	}

	SetViewport();
}

void D3D::Destroy()
{
	SAFE_DELETE(Instance);
}

void D3D::SetRenderTarget(ID3D11RenderTargetView* RTV, ID3D11DepthStencilView* DSV)
{
	if (RTV == nullptr)
		RTV = RenderTargetView;
	if (DSV == nullptr)
		DSV = DepthStencilView;

	DeviceContext->OMSetRenderTargets(1, &RTV, DSV);
}

void D3D::Clear(Vector3 Color, ID3D11RenderTargetView* RTV, ID3D11DepthStencilView* DSV)
{
	if (RTV == nullptr)
		RTV = RenderTargetView;
	if (DSV == nullptr)
		DSV = DepthStencilView;

	SetRenderTarget(RTV, DSV);

	float color[4] = { Color.X, Color.Y, Color.Z, 1.0f };
	DeviceContext->ClearRenderTargetView(RTV, color);
	DeviceContext->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH, 1, 0);

	//float clearColor[4] = { Desc.Background.x, Desc.Background.y, Desc.Background.z, Desc.Background.w };
	//DeviceContext->ClearRenderTargetView(RTV, clearColor);
	//DeviceContext->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3D::Present()
{
	SwapChain->Present(0, 0);
}

void D3D::DepthTest()
{
	D3D11_TEXTURE2D_DESC depthDesc;
	DepthBuffer->GetDesc(&depthDesc);

	D3D11_TEXTURE2D_DESC desc = depthDesc;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.MiscFlags = 0;

	ID3D11Texture2D* texture = nullptr;
	Device->CreateTexture2D(&desc, nullptr, &texture);

	D3D11_MAPPED_SUBRESOURCE mapResource;
	DeviceContext->Map(texture, 0, D3D11_MAP_READ, 0, &mapResource);

	UINT width, height;
	width = WIN_WIDTH;
	height = WIN_HEIGHT;

	float* depthData = new float[width * height];

	BYTE* mapData = static_cast<BYTE*>(mapResource.pData);
	for (UINT y = 0; y < height; ++y)
	{
		for (UINT x = 0; x < width; ++x)
		{
			UINT depthIndex = y * mapResource.RowPitch + x * 4;
			//float depthValue = *(reinterpret_cast<float*>(mapData) * depthIndex);
			UINT depthValue = *(reinterpret_cast<UINT*>(mapData + depthIndex)) & 0xFFFFFF; // 24비트 깊이 값 추출
			float normalizedDepth = static_cast<float>(depthValue) / static_cast<float>(0xFFFFFF);
			depthData[y * width + x] = depthValue / D3D11_FLOAT32_MAX;
		}
	}

	//stbi_write_png("Depth.png", width, height, 1, depthData, width * sizeof(float));

	delete[] depthData;
	DeviceContext->Unmap(texture, 0);
	texture->Release();
}

void D3D::SetViewport()
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
#endif // MODE == 0


#if MODE == 1
D3D::D3D()
	:Numerator(0), Denominator(1)
{
	CONSTRUCTOR_DEBUG();

}

D3D::~D3D()
{
	DESTRUCTOR_DEBUG();

	SAFE_RELEASE(Device);
	SAFE_RELEASE(DeviceContext);

	SAFE_RELEASE(Buffer);

	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(DepthStencilView);
}

D3D* D3D::Get()
{
	if (Instance == nullptr)
		Instance = new D3D();

	return Instance;
}

void D3D::Destroy()
{
	SAFE_DELETE(Instance);
}

void D3D::Create()
{
	SetGPUInfo();

	CreateSwpaChainAndDevice();
	CreateBackBuffer(static_cast<float>(Desc.Width), static_cast<float>(Desc.Height));
}

void D3D::SetRenderTarget(ID3D11RenderTargetView* RTV, ID3D11DepthStencilView* DSV)
{
	if (RTV == nullptr)
		RTV = RenderTargetView;
	if (DSV == nullptr)
		DSV = DepthStencilView;

	DeviceContext->OMSetRenderTargets(1, &RTV, DSV);
}

void D3D::Clear(Vector3 Color, ID3D11RenderTargetView* RTV, ID3D11DepthStencilView* DSV)
{
	if (RTV == nullptr)
		RTV = RenderTargetView;
	if (DSV == nullptr)
		DSV = DepthStencilView;

	float color[4] = { Color.X, Color.Y, Color.Z, 1.0f };
	DeviceContext->ClearRenderTargetView(RTV, color);
	DeviceContext->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH, 1, 0);
}

void D3D::Present()
{
	SwapChain->Present(Desc.bVsync == true ? 1 : 0, 0);
}

void D3D::ResizeScreen(const float Width, const float Height)
{

}

void D3D::SetGPUInfo()
{
	HRESULT result;
	IDXGIFactory* factory;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	CHECK(result);

	IDXGIAdapter* adapter;
	result = factory->EnumAdapters(0, &adapter);
	CHECK(result);

	IDXGIOutput* adapterOutput;
	result = adapter->EnumOutputs(0, &adapterOutput);
	CHECK(result);

	UINT modeCount;
	result = adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		nullptr
	);
	CHECK(result);

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[modeCount];
	result = adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		displayModeList
	);
	CHECK(result);

	for (UINT i = 0; i < modeCount; i++)
	{
		bool isCheck = true;
		isCheck &= displayModeList[i].Width == Desc.Width;
		isCheck &= displayModeList[i].Height == Desc.Height;

		if (isCheck == true)
		{
			Numerator = displayModeList[i].RefreshRate.Numerator;
			Denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC desc;
	result = adapter->GetDesc(&desc);
	CHECK(result);

	GPUMemorySize = static_cast<UINT>(desc.DedicatedVideoMemory) / 1024 / 1024;
	GPUDesc = desc.Description;

	SAFE_DELETE_ARRAY(displayModeList);

	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);
}

void D3D::CreateSwpaChainAndDevice()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (Desc.bVsync == true)
	{
		desc.BufferDesc.RefreshRate.Numerator = Numerator;
		desc.BufferDesc.RefreshRate.Denominator = Denominator;
	}
	else
	{
		desc.BufferDesc.RefreshRate.Numerator = 0;
		desc.BufferDesc.RefreshRate.Denominator = 1;
	}

	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = Desc.Handle;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = !Desc.bFullScreen;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = 0;

	UINT createionFalgs = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	HRESULT result = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createionFalgs,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&desc,
		&SwapChain,
		&Device,
		nullptr,
		&DeviceContext
	);
	CHECK(result);
}

void D3D::CreateBackBuffer(const float Width, const float Height)
{
	HRESULT result;
	{
		ID3D11Texture2D* backBuffer;
		result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		CHECK(result);

		result = D3D::GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &RenderTargetView);
		CHECK(result);

		SAFE_RELEASE(backBuffer);
	}

	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = static_cast<UINT>(Width);
		desc.Height = static_cast<UINT>(Height);
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		result = Device->CreateTexture2D(&desc, nullptr, &Buffer);
		CHECK(result);
	}

	{
		D3D11_DEPTH_STENCIL_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		result = Device->CreateDepthStencilView(Buffer, &desc, &DepthStencilView);
		CHECK(result);

		SetRenderTarget(RenderTargetView, DepthStencilView);
	}
}

void D3D::DeleteBackBuffer()
{
	SAFE_RELEASE(DepthStencilView);
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(Buffer);
}
#endif
