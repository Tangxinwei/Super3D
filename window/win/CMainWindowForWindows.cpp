#include "CMainWindowForWindows.h"
#include <stdint.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool CMainWindowForWindows::initWindow(CCreationParams& params)
{
	const TCHAR *className = __TEXT("Super3D");
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.lpszClassName = className;
	RegisterClassEx(&wcex);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	DWORD style = WS_POPUP;
	if(!params.fullScreen)
		style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	else
	{
		params.height = screenHeight;
		params.width = screenWidth;
	}
	hwnd = CreateWindowW(className, __TEXT(""), style, (screenWidth - params.width) / 2, (screenHeight - params.height) / 2, \
		params.width, params.height, NULL, NULL, wcex.hInstance, NULL);
	params.windowHandler = hwnd;
	ShowWindow(hwnd, SW_SHOW);
	return CMainWindow::initWindow(params);
}

bool CMainWindowForWindows::run()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			return false;
	}
	return true;
}