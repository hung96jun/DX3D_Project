#pragma once
//#include "Utilities/DataStructs.h "
#include "DataStructs/Color.h"

struct D3DDesc
{
	wstring AppName;
	HINSTANCE Instance;
	HWND Handle;
	float Width;
	float Height;
	bool bVsync;
	bool bFullScreen;
	Color Background;
};

class D3D
{
private:
	D3D();
	~D3D();

	void SetGPUInfo();
	void CreateSwapChainAndDevice();

	void CreateBackBuffer(float width, float height);
	void DeleteBackBuffer();

public:
	static D3D* Get();

	static void Create();
	static void Delete();

	static const float Width() { return Desc.Width; }
	static const float Height() { return Desc.Height; }

	static ID3D11Device* GetDevice() { return Device; }
	static ID3D11DeviceContext* GetDC() { return DeviceContext; }
	static IDXGISwapChain* GetSwapChain() { return SwapChain; }
	static const D3DDesc& GetDesc() { return Desc; }
	static void SetDesc(D3DDesc& desc) { Desc = desc; }

	void SetRendertarget(ID3D11RenderTargetView* rtv = nullptr, ID3D11DepthStencilView* dsv = nullptr);

	void Clear(Color color = Color(0.0f, 0.125f, 0.3f, 1.0f), ID3D11RenderTargetView* rtv = nullptr, ID3D11DepthStencilView* dsv = nullptr);
	void Present();

	void ResizeScreen(float width, float height);

private:
	static D3D* Instance;

	static D3DDesc Desc;
	static ID3D11Device* Device;
	static ID3D11DeviceContext* DeviceContext;
	static IDXGISwapChain* SwapChain;

	ID3D11Debug* DebugDevice;

	UINT GPUMenorySize;
	wstring GPUDescriptoin;

	UINT Numerator;
	UINT Denominator;

	ID3D11Texture2D* BackBuffer;
	ID3D11DepthStencilView* DepthStencilView;
	ID3D11RenderTargetView* RenderTargetView;
};