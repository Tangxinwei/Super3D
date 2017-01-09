#include <window\CMainWindow.h>
#include <input\IInput.h>
#include <common\CCreationParams.h>

int main()
{
	CMainWindow* main = createMainWindow(render::DT_DX11);
	createInputEventDevice(render::DT_DX11);
	CCreationParams params;
	params.windowHandler = main->getWindowHandler();
	main->initWindow(params);
	main->mainLoop();
	delete main;
	return 0;
}