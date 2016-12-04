#include <window\CMainWindow.h>

#ifdef _WINDOWS
	#include <window\win\CMainWindowForWindows.h>
#endif

#include <common\CCreationParams.h>

int main()
{
	CMainWindow* main = new CMainWindowForWindows;
	CCreationParams params;
	params.windowHandler = main->getWindowHandler();
	main->initWindow(params);
	main->mainLoop();
	delete main;
	return 0;
}