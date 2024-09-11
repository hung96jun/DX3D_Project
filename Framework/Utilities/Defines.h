#pragma once

//#define WIN_WIDTH 1920
//#define WIN_HEIGHT 1080
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
//#define WIN_WIDTH 1280
//#define WIN_HEIGHT 720

#define MAX_LIGHT 10
#define MAX_BONE 1024
#define MAX_FRAME 1024
#define MAX_INSTANCE 128

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define SUPER __super

//#define DEVICE GameInstance::GetDevice()->GetDevice()
//#define DC GameInstance::GetDevice()->GetDeviceContext()
//
//#define KEY_DOWN(k) GameInstance::GetKeyboard()->Down(k)
//#define KEY_UP(k) GameInstance::GetKeyboard()->Up(k)
//#define KEY_PRESS(k) GameInstance::GetKeyboard()->Press(k)

#define CHECK(x) { assert(SUCCEEDED(x)); }

#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = nullptr; }}
#define SAFE_DELETE(x) { if(x) { delete (x); (x) = nullptr; }}
#define SAFE_DELETE_ARRAY(x) { if(x) { delete [] (x); (x) = nullptr; }}

#define GMAE_MODE 0
#define	ANIM_MODE 0

#define DEBUG 1

#define DIALOG ImGuiFileDialog::Instance()
