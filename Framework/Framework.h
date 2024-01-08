#pragma once

//#include "targetver.h"
#include <SDKDDKVer.h>

#define _CRTDBG_MAP_ALLOC

#define WIN32_LEAN_AND_MEAN

#include "Utilities/Defines.h"

// STL
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <assert.h>
#include <crtdbg.h>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <DirectXCollision.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <ImGuiFileDialog.h>
#include <d2d1_2.h>
#include <dwrite.h>
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "ImGui.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "assimp-vc143-mtd.lib")

using namespace std;
using namespace DirectX;
using namespace DirectX::TriangleTests;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
//typedef XMVECTOR Vector4;
typedef XMMATRIX Matrix;
typedef XMFLOAT4X4 Float4x4;

#include "Math/Vector.h"

#include "Systems/D3D.h"
//#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
//#include "Systems/Time.h"
/**
* Framwork에 keyboard 헤더를 참조하고, keyboard에서 Framework 헤더를 참조해서 LNK4006 경고가 발생.
* 아마 Mosue도 Framework에 참조하면 동일한 문제가 추가로 발생할 것 같다.
* 경고는 연산자 재정의 한것이 중복으로 정의되었으므로 초정의가 무시된다는 경고이다.
* 추후 정보를 찾아서 수정하는 방향으로 진행
*/
