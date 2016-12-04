#pragma once
#include "../CMainWindow.h"
#include<Windows.h>


class CMainWindowForWindows : public CMainWindow
{
private:
	HWND hwnd;
public:
	virtual bool initWindow(CCreationParams& params);
	virtual bool run();
	virtual void* getWindowHandler() { return hwnd; }
};