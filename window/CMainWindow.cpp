#pragma once
#include "CMainWindow.h"
#ifdef _WINDOWS
	#include "win\CMainWindowForWindows.h"
#endif
CMainWindow* main = NULL;
CMainWindow* createMainWindow(render::DeviceType dt)
{
	switch (dt)
	{
	case render::DT_DX11:
		main = new CMainWindowForWindows;
		return main;
	}
	return NULL;
}
CMainWindow* getMainWindowInstance()
{
	return main;
}