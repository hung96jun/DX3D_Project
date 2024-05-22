#pragma once
#include "Libraries.h"

#include "Utilities/Defines.h"

struct WindowDesc
{
	wstring AppName;
	HINSTANCE Instance;
	HWND Handle;
	UINT Width;
	UINT Height;
	bool bVsync;
	bool bFullScreen;
	Float4 Background;
};

class D3D
{
private:
	D3D();
	~D3D();

public:
	static D3D* Get();
	static void Destroy();
	void Create();

	void Clear();
	void Present();

	void SetDesc(WindowDesc& Value) { Desc = Value; }
	static WindowDesc& GetDesc() { return Desc; }

	static ID3D11Device* GetDevice() { return Device; }
	static ID3D11DeviceContext* GetDC() { return DeviceContext; }

private:
	void DeviceSetting();
	void BackBufferSetting();
	void DepthStencilViewSetting();
	void DepthStencilStateSetting();
	void ViewportSetting();

private:
	static D3D* Instance;

	static ID3D11Device* Device;
	static ID3D11DeviceContext* DeviceContext;

	static WindowDesc Desc;

	IDXGISwapChain* SwapChain;
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11DepthStencilView* DepthStencilView;
	ID3D11DepthStencilState* DepthStencilState;
};

