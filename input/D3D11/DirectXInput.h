#pragma once
#include "../IInput.h"
#include <D3D11.h>
#include <DxErr.h> 
#include <D3DCompiler.h>
#include <D3DX11async.h>
#include <dinput.h>
#include <window\CMainWindow.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class DirectXInputEventDevice : public InputEventDevice
{
private:
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 keyboard;
	LPDIRECTINPUTDEVICE8 mouse;
	char keys[256];
	DIMOUSESTATE mouseState;
public:
	DirectXInputEventDevice()
	{
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dinput, NULL);
		dinput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
		dinput->CreateDevice(GUID_SysMouse, &mouse, NULL);
		keyboard->SetDataFormat(&c_dfDIKeyboard);
		mouse->SetDataFormat(&c_dfDIMouse);
		keyboard->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		mouse->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		keyboard->Acquire();
		mouse->Acquire();
	}

	virtual ~DirectXInputEventDevice()
	{
		keyboard->Unacquire();
		mouse->Unacquire();
		SafeRelease(keyboard);
		SafeRelease(mouse);
		SafeRelease(dinput);
	}

	virtual bool checkKeyIsDown(int key)
	{
		return keys[key] & 0x80;
	}

	virtual bool checkMouseKeyIsDown(int mouseKey)
	{
		return mouseState.rgbButtons[mouseKey] & 0x80;
	}

	virtual bool updateState()
	{
		keyboard->GetDeviceState(sizeof(keys), (void*)&keys);
		mouse->GetDeviceState(sizeof(mouseState), (void*)&mouseState);
		if (mouseState.lX || mouseState.lY)
		{
			onMouseMove(mouseState.lX, mouseState.lY);
		}
		return true;
	}
	virtual vec2 getMousePosition()
	{
		POINT pt;
		HWND hwnd = (HWND)getMainWindowInstance()->getWindowHandler();
		GetCursorPos(&pt);
		ScreenToClient(hwnd, &pt);
		return vec2(pt.x, pt.y);
	}
};

