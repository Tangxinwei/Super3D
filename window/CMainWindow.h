#pragma once
#include <common\CCreationParams.h>
#include <render\IDevice.h>

class CMainWindow
{
protected:
	CCreationParams createParams;
	render::IDevice *pDevice;
public:
	virtual ~CMainWindow() {}
	virtual bool initWindow(CCreationParams& params)
	{
		this->createParams = params;
		this->pDevice = render::createDevice(params);
		return this->pDevice != NULL;
	}
	virtual bool run() = 0;
	virtual void* getWindowHandler() = 0;
	void mainLoop()
	{
		while (this->run())
		{
			pDevice->beginScene();
			pDevice->endScene();
		}
	}
};