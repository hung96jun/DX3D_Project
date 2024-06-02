#pragma once
#include "Libraries.h"
#include "Math/Vector.h"
#include "Utilities/Defines.h"

#define MODE 1

struct WindowDesc
{
	wstring AppName;
	HINSTANCE Instance;
	HWND Handle;
	UINT Width;
	UINT Height;
	bool bVsync;
	bool bFullScreen;
	Vector3 Background;
};

#if MODE == 0
class D3D
{
private:
	D3D();
	~D3D();

public:
	static D3D* Get();
	static void Destroy();
	void Create();

	void SetDesc(WindowDesc& Value) { Desc = Value; }
	static WindowDesc& GetDesc() { return Desc; }

	static ID3D11Device* GetDevice() { return Device; }
	static ID3D11DeviceContext* GetDC() { return DeviceContext; }

	void SetRenderTarget(ID3D11RenderTargetView* RTV = nullptr, ID3D11DepthStencilView* DSV = nullptr);

	void Clear(Vector3 Color, ID3D11RenderTargetView* RTV = nullptr, ID3D11DepthStencilView* DSV = nullptr);
	void Present();

	void DepthTest();

private:
	void SetViewport();

private:
	static D3D* Instance;

	static ID3D11Device* Device;
	static ID3D11DeviceContext* DeviceContext;

	static WindowDesc Desc;

	IDXGISwapChain* SwapChain;

	ID3D11Texture2D* DepthBuffer;
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11DepthStencilView* DepthStencilView;
}; 
#endif

#if  MODE == 1
class D3D
{
private:
	D3D();
	~D3D();

public:
	static D3D* Get();
	static void Destroy();
	void Create();

	static const float Width() { return static_cast<float>(Desc.Width); }
	static const float Height() { return static_cast<float>(Desc.Height); }

	static ID3D11Device* GetDevice() { return Device; }
	static ID3D11DeviceContext* GetDC() { return DeviceContext; }
	static IDXGISwapChain* GetSwpaChain() { return SwapChain; }
	static const WindowDesc& GetDesc() { return Desc; }

	static void SetDesc(WindowDesc& WndDesc)
	{
		Desc = WndDesc;
	}

	void SetRenderTarget(ID3D11RenderTargetView* RTV = nullptr, ID3D11DepthStencilView* DSV = nullptr);

	void Clear(Vector3 Color, ID3D11RenderTargetView* RTV = nullptr, ID3D11DepthStencilView* DSV = nullptr);
	void Present();

	void ResizeScreen(const float Width, const float Height);

private:
	void SetGPUInfo();
	void CreateSwpaChainAndDevice();

	void CreateBackBuffer(const float Width, const float Height);
	void DeleteBackBuffer();

private:
	static D3D* Instance;

	static WindowDesc Desc;
	static ID3D11Device* Device;
	static ID3D11DeviceContext* DeviceContext;
	static IDXGISwapChain* SwapChain;

	ID3D11Debug* DebugDevice;

	UINT GPUMemorySize;
	wstring GPUDesc;

	UINT Numerator;
	UINT Denominator;

	ID3D11Texture2D* Buffer;
	ID3D11DepthStencilView* DepthStencilView;
	ID3D11RenderTargetView* RenderTargetView;
};
#endif