#pragma once
#include "Libraries.h"

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
	static D3D* Instance;

	static ID3D11Device* Device;
	static ID3D11DeviceContext* DeviceContext;

	static WindowDesc Desc;

	IDXGISwapChain* SwapChain;
	ID3D11RenderTargetView* RenderTargetView;
};

